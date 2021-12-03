#include <iostream>
#include <assert.h>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <time.h>
#include <algorithm>
#include <ctime>
#include <cmath>

#include "configure.h"

using namespace std;

int main()
{
    // ������������������
    const int num_player = 6;
    // ���Ժ���ָ�����飬�����ڴ������Լ��Ĳ���
    // �˴�+1��Ϊ�������id�ʹ����idһ��
    //enum Decision(*f[num_player + 1])(int rs, int len, int my_id, const char my_decisions[], int opp_id, const char opp_decisions[], const int repay[MAX_TURN][4], const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN], const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN]);
    enum Decision(*f[num_player + 1])(int, int, int, const char[], int, const char[], const int[][4], const char[][MAX_TURN], const char[][MAX_TURN]);
    for (int i = 1; i <= num_player; i++) f[i] = PROTOTYPE;

    // �ڶԿ�֮ǰ��������ʷ���߼�¼�ļ�
    ofstream streams[num_player + 1];
    for (int i = 1; i <= num_player; i++)
    {
        streams[i].open("record_" + to_string(i) + ".txt");
    }


    int scores[num_player + 1] = { 0 };	// �������ܵ÷�
    int r_idx;						// ��ǰ�ִ�
    for (r_idx = 0; r_idx < MAX_ROUND; r_idx++)
    {
        unsigned seed;
        seed = (unsigned int)time(0);
        srand(seed);

        // |             | COOPERATION | BETRAYAL |
        // |-------------|-------------|----------|
        // | COOPERATION | R,R         | S,T      |
        // | BETRAYAL    | T,S         | P,P      |
        // Temptation	���ѵ��ջ�
        // Suckers		��ƭ�Ĵ���֧��
        // Reward		�����ı���
        // Punishment	˫�����ѵ��ϳ�

        // ���ɶԿ��ִ�
        int cases[MAX_TURN][4]; // ����ÿ�ֶԿ��Ļر�: cases[][Temptation, Suckers, Reward, Punishment]
        for (int i = 0; i < MAX_TURN; i++)
        {
            // ���ɷ��������ο�������Ȩ��������
            int delta = log(log(i + 2.0));
            cases[i][0] = 2 * delta;
            cases[i][1] = -3 * delta;
            cases[i][2] = 1 * delta;
            cases[i][3] = -2 * delta;
        }

        // ���ɶԿ�˳��
        vector<pair<int, int>> order;
        for (int i = 1; i <= num_player; i++)
        {
            for (int j = i + 1; j <= num_player; j++)
            {
                order.push_back(pair<int, int>(i, j));
            }
        }
        // ���ҶԿ�˳��
        shuffle(order.begin(), order.end(), default_random_engine((unsigned)time(NULL)));

        // ��ʼ�Կ�
        int id_a, id_b, score_a, score_b;
        char choice_a[MAX_TURN + 1], choice_b[MAX_TURN + 1], a, b;
        choice_a[MAX_TURN] = '\0';
        choice_b[MAX_TURN] = '\0';
        // �������жԿ���
        for (auto iter = order.begin(); iter != order.end(); iter++)
        {
            id_a = iter->first;
            id_b = iter->second;
            score_a = 0, score_b = 0;

            // ��ȡ a �Ĳ�����ʷ
            char a_history_decisions[HISTORY_LENGTH][MAX_TURN];
            char a_opp_history_decisions[HISTORY_LENGTH][MAX_TURN];
            // �������20��
            string a_file = "record_" + to_string(id_a) + ".txt";
            int a_file_length;
            ifstream tool(a_file);
            string line;
            for (a_file_length = 0; getline(tool, line); a_file_length++);
            tool.close();
            // �ж�20����ʷ��ϢҪ��������ļ���
            int start_idx = 0;
            int start_line = 0;
            if ((a_file_length / 3) >= HISTORY_LENGTH)
            {
                start_idx = 0;
                start_line += (a_file_length / 3 - HISTORY_LENGTH) * 3;
            }
            else
            {
                start_idx = HISTORY_LENGTH - (a_file_length / 3);
                start_line = 0;
            }
            // ������Ϣ��λ����m���
            for (int idx = 0; idx < start_idx; idx++)
            {
                for (int kk = 0; kk < 25; kk++)
                {
                    a_history_decisions[idx][kk] = 'm';
                    a_opp_history_decisions[idx][kk] = 'm';
                }
            }
            // ������Ϣ��λ������ʷ���
            tool.open(a_file);
            int file_line_idx = 0;
            int his_idx = start_idx;
            while (std::getline(tool, line))
            {
                if ((file_line_idx > start_line) && (file_line_idx % 3 == 2))
                {
                    // line �ֳ������ֵľ��߽��
                    for (int kk = 0; kk < 25; kk++)
                    {
                        a_history_decisions[his_idx][kk] = line[kk];
                        a_opp_history_decisions[his_idx][kk] = line[26 + kk];
                    }
                    his_idx++;
                }
                file_line_idx++;
            }
            tool.close();
            // ��һ��������ʧ����Ϣ��20����Խ����ԽԶ����Խ��
            for (int idx = 0; idx < HISTORY_LENGTH; idx++)
            {
                double possibility = fabs(idx - 9.5) / 8;
                bool lose = false;
                if ((rand() % 100 / 10.) < possibility)
                {
                    lose = true;
                }
                if (lose)
                {
                    for (int kk = 0; kk < MAX_TURN; kk++)
                    {
                        a_history_decisions[idx][kk] = 'm';
                        a_opp_history_decisions[idx][kk] = 'm';
                    }
                }
            }

            // ��ȡ b �Ĳ�����ʷ
            char b_history_decisions[HISTORY_LENGTH][MAX_TURN];
            char b_opp_history_decisions[HISTORY_LENGTH][MAX_TURN];
            // �������20��
            string b_file = "record_" + to_string(id_b) + ".txt";
            int b_file_length;
            tool.open(b_file);
            for (b_file_length = 0; getline(tool, line); b_file_length++);
            tool.close();
            // �ж�20����ʷ��ϢҪ��������ļ���
            start_idx = 0;
            start_line = 0;
            if ((b_file_length / 3) >= HISTORY_LENGTH)
            {
                start_idx = 0;
                start_line += (b_file_length / 3 - HISTORY_LENGTH) * 3;
            }
            else
            {
                start_idx = HISTORY_LENGTH - (b_file_length / 3);
                start_line = 0;
            }
            // ������Ϣ��λ����m���
            for (int idx = 0; idx < start_idx; idx++)
            {
                for (int kk = 0; kk < 25; kk++)
                {
                    b_history_decisions[idx][kk] = 'm';
                    b_opp_history_decisions[idx][kk] = 'm';
                }
            }
            // ������Ϣ��λ������ʷ���
            tool.open(b_file);
            file_line_idx = 0;
            his_idx = start_idx;
            while (std::getline(tool, line))
            {
                if ((file_line_idx > start_line) && (file_line_idx % 3 == 2))
                {
                    // line �ֳ������ֵľ��߽��
                    for (int kk = 0; kk < 25; kk++)
                    {
                        b_history_decisions[his_idx][kk] = line[kk];
                        b_opp_history_decisions[his_idx][kk] = line[26 + kk];
                    }
                    his_idx++;
                }
                file_line_idx++;
            }
            tool.close();
            // ��һ��������ʧ����Ϣ��20����Խ����ԽԶ����Խ��
            for (int idx = 0; idx < HISTORY_LENGTH; idx++)
            {
                double possibility = fabs(idx - 9.5) / 8;
                bool lose = false;
                if ((rand() % 100 / 10.) < possibility)
                {
                    lose = true;
                }
                if (lose)
                {
                    for (int kk = 0; kk < MAX_TURN; kk++)
                    {
                        b_history_decisions[idx][kk] = 'm';
                        b_opp_history_decisions[idx][kk] = 'm';
                    }
                }
            }

            // ���ֶ�ս��ʼ
            for (int k = 0; k < MAX_TURN; k++)
            {
                a = (char)f[id_a](r_idx, k, id_a, choice_a, id_b, choice_b, cases, b_history_decisions, b_opp_history_decisions);
                b = (char)f[id_b](r_idx, k, id_b, choice_b, id_a, choice_a, cases, a_history_decisions, a_opp_history_decisions);
                choice_a[k] = a;
                choice_b[k] = b;

                // |             | COOPERATION | BETRAYAL |
                // |-------------|-------------|----------|
                // | COOPERATION | R,R         | S,T      |
                // | BETRAYAL    | T,S         | P,P      |
                // Temptation	���ѵ��ջ�
                // Suckers		��ƭ�Ĵ���֧��
                // Reward		�����ı���
                // Punishment	˫�����ѵ��ϳ�
                // cases[][Temptation, Suckers, Reward, Punishment]

                // ����÷�
                if (a == COOPERATION && b == COOPERATION) {
                    score_a += cases[k][2];
                    score_b += cases[k][2];
                }
                else if (a == COOPERATION && b == BETRAYAL) {
                    score_a += cases[k][1];
                    score_b += cases[k][0];
                }
                else if (a == BETRAYAL && b == COOPERATION) {
                    score_a += cases[k][0];
                    score_b += cases[k][1];
                }
                else if (a == BETRAYAL && b == BETRAYAL) {
                    score_a += cases[k][3];
                    score_b += cases[k][3];
                }
                else {
                    cout << "Warning: illegal decision: a=" << a << ", b=" << b << ", in turn " << k << ", round " << r_idx << endl;
                }
            }
            scores[id_a] += score_a;
            scores[id_b] += score_b;
            // ������ֽ��
            cout << id_a << " V.S. " << id_b << endl;
            cout << score_a << " " << score_b << endl;
            cout << choice_a << " " << choice_b << endl;
            // ����ս��Ϣд���ļ�
            streams[id_a] << id_a << " " << id_b << endl;
            streams[id_a] << score_a << " " << score_b << endl;
            streams[id_a] << choice_a << " " << choice_b << endl;
            streams[id_a].flush();
            streams[id_b] << id_b << " " << id_a << endl;
            streams[id_b] << score_b << " " << score_a << endl;
            streams[id_b] << choice_b << " " << choice_a << endl;
            streams[id_b].flush();
        }
    }


    // ���������е÷�
    for (int i = 1; i <= num_player; i++)
    {
        cout << "player " << i << ": " << scores[i] << endl;
    }

    for (int i = 1; i <= num_player; i++)
    {
        streams[i].close();
    }


    system("pause");
    return 0;
}