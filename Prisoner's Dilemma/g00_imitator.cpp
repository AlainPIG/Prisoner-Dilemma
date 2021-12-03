#include <stdio.h>
#include <limits.h>
#include "configure.h"

// ���ӱ��ζ�ս���̣���ʷ���Ų��Ը�����
enum Decision g00_imitator(	int rs, 
							int len,
							int my_id,
							const char *my_decisions,
							int opp_id,
							const char *opp_decisions ,
							const int repay[MAX_TURN][4],
							const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN],
							const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN])
{
    bool find = false;
    //���Է��ж�ս��¼���ҵ�������ʷ��ս�е÷���͵�һ�֣�ģ�����Ķ���
    int min_score = INT_MAX;
    int min_decision_idx = 0;
    for(int i=0;i<HISTORY_LENGTH;i++)
    {
        int score = 0;
        for(int j=0;j<MAX_TURN;j++)
        {
            if(opp_history_decisions[i][j] == COOPERATION && opp_opp_history_decisions[i][j] == COOPERATION)
            {
                score += 3;
            }
            else if(opp_history_decisions[i][j] == COOPERATION && opp_opp_history_decisions[i][j] == BETRAYAL)
            {
                score -= 1;
            }
            else if(opp_history_decisions[i][j] == BETRAYAL && opp_opp_history_decisions[i][j] == COOPERATION)
            {
                score += 5;
            }
            else
            {
                score -= 3;
            }
        }
        if(score < min_score)
        {
            min_score = score;
            min_decision_idx = i;
            find = true;
        }
    }
    if(find)
    {
        if(opp_opp_history_decisions[min_decision_idx][len]=='c')
            return COOPERATION;
        else
            return BETRAYAL;
    }
	// ���Է��޶�ս��¼ ������ѡ�����
    else
    {
		return COOPERATION;
	}
}
