#include<iostream>
#include<math.h>
#include<random>
#include<time.h>
#include"configure.h"

enum Decision PROTOTYPE(int rs,
	int len,
	int my_id,
	const char* my_decisions,
	int opp_id,
	const char* opp_decisions,
	const int repay[MAX_TURN][4],
	const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN],
	const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN])
{

	// **********************************************************
	// **********************************************************

	// ����ϵͳ����
	static const double LAUNCHER = 0.5, RECEIVER = 0.2, BETRAYER = 0.1;
	//  --------------------------------
	//  |  LAUNCHER  |     ������     |
	//  |  RECEIVER  |     ���ܽ���     |
	//  |  BETRAYER  |   ���ѳͷ�ϵ��   |
	//  --------------------------------
	static double my_credit = 0.8, opp_credit = 0.8;	// ˫��������
	static enum { _100, _101, _302 } protocol_code = _100;	// Э�����
	// ������䶨����ÿ��˫������������ֵ�ͳͷ�ϵ��
	//		������� static �ؼ���, ������ͻ᲻�ϼ̳е��������Ļغ�
	//		�������, ������������֮ǰ���ñ��ֶԵ�ǰ�غϵ�Ӱ��
	static double my_reward = 0, my_punishment = 1,
		opp_reward = 0, opp_punishment = 1;
	static const double decay = 0.9;
	//  --------------------------------
	//  |    reward    |     ����ֵ     |
	//  |  punishment  |    �ͷ�ϵ��    |
	//  |    decay     |    ˥��ϵ��    |
	//  --------------------------------
	if (len == 1) {
		if (opp_decisions[0] == 'c') {
			opp_reward = LAUNCHER;
			if (my_decisions[0] == 'b') {
				protocol_code = _101;
			}
			else {
				my_reward = LAUNCHER;
				protocol_code = _100;
			}
		}
		else {
			if (my_decisions[0] == 'b') {
				protocol_code = _302;
			}
			else {
				my_reward = LAUNCHER;
				protocol_code = _101;
			}
		}
	}
	else if (len >= 2) {
		switch (protocol_code) {
		case _101:
			if (my_decisions[len - 2] == 'c') {
				if (opp_decisions[len - 1] == 'b') {
					protocol_code = _302;
				}
				else {
					opp_reward = RECEIVER;
					protocol_code = _100;
				}
			}
			else {
				if (my_decisions[len - 1] == 'b') {
					protocol_code = _302;
				}
				else {
					my_reward = RECEIVER;
					protocol_code = _100;
				}
			}
			break;
		case _100:
			if (my_decisions[len - 1] == 'b') {
				my_punishment = BETRAYER;
				protocol_code = _302;
			}
			if (opp_decisions[len - 1] == 'b') {
				opp_punishment = BETRAYER;
				protocol_code = _302;
			}
			break;
		case _302:
			if (opp_decisions[len - 1] == 'c') {
				opp_reward = LAUNCHER;
				if (my_decisions[len - 1] == 'b') {
					protocol_code = _101;
				}
				else {
					my_reward = LAUNCHER;
					protocol_code = _100;
				}
			}
			else {
				if (my_decisions[len - 1] == 'c') {
					my_reward = LAUNCHER;
					protocol_code = _101;
				}
			}
			// ����������: 
			// ����˫�����ھܾ�Э��״̬, Ҳ��һ������Ȼ�����Է�������Э��
			// (��Ȼ����Ȼ�����������˥����, ���Ҫ��������)
		}
	}
	my_credit = (my_credit + my_reward) * my_punishment * decay;
	opp_credit = (opp_credit + opp_reward) * opp_punishment * decay;
	if (my_credit > 1) {
		my_credit = 1;
	}
	if (opp_credit > 1) {
		opp_credit = 1;
	}

	// **********************************************************
	// **********************************************************

	// ����ϵͳ����
	static const double probability_power = 0.5;
	// ���ݶԷ������ּ������
	double probability = pow(opp_credit, probability_power);

	// ���� 0~1 ֮����ȷֲ��������
	double random_number;
	static int seed_number = 52;
	// seed_number ��Ϊ����������������ֵ�߱������������һ�� "������"
	// ԭ��������ֵ��������ѡȡ

	std::default_random_engine engine;
	unsigned int time_now = time(NULL);
	engine.seed(time_now + seed_number);
	// ѡȡ "��ǰʱ�� + ������" Ϊα����������ɳ�ʼֵ
	std::uniform_real_distribution<double> get_random_number(0, 1);
	random_number = get_random_number(engine);
	/*	���Դ���, ���ڼ�������
	std::cout << random_number << std::endl;
	*/
	seed_number += 4;
	// ÿ�α���ı�һ�� seed_number ��ֵ�Ա�֤�����

	// ��ʼ����
	switch (len) {
	case 0:
		if (random_number < probability) {
			return Decision::COOPERATION;
		}
		else {
			return Decision::BETRAYAL;
		}
		break;
	default:
		switch (protocol_code) {
		case _100:
			return Decision::COOPERATION;
			break;
		case _101:
			if (my_decisions[len - 1] == 'c') {
				return Decision::BETRAYAL;
			}
			else {
				if (random_number < probability) {
					return Decision::COOPERATION;
				}
				else {
					return Decision::BETRAYAL;
				}
			}
			break;
		case _302:
			if (random_number < probability) {
				return Decision::COOPERATION;
			}
			else {
				return Decision::BETRAYAL;
			}
		}
	}
}