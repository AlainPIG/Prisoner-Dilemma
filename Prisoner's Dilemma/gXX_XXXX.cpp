#include<iostream>
#include<math.h>
#include<random>
#include<time.h>

#include"configure.h"
#include"protocol.h"

enum Decision gXX_YYYY(int rs,
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
	//
	// ��һ���ֵĳ��򽫷�װ�� credit.cpp ��
	static double my_credit = 0.7, opp_credit = 0.7;	// ˫����ʼ������
	static enum protocol_code protocol_code = _100;	// Э�����
	// ������䶨����ÿ��˫������������ֵ�ͳͷ�ϵ��
	//		������� static �ؼ���, ������ͻ᲻�ϼ̳е��������Ļغ�
	//		�������, ������������֮ǰ���ñ��ֶԵ�ǰ�غϵ�Ӱ��
	static double my_reward = 0, my_punishment = 1,
		opp_reward = 0, opp_punishment = 1;
	//  --------------------------------
	//  |    reward    |     ����ֵ     |
	//  |  punishment  |    �ͷ�ϵ��    |
	//  --------------------------------

	// ���� 1: ���������������ʷ��¼��ʼ���Է�������
	
	for (size_t HISTORY = 0;HISTORY < HISTORY_LENGTH;++HISTORY) {
		for (size_t TURN = 0; TURN < MAX_TURN;++TURN) {
			credit(opp_opp_history_decisions[HISTORY],
				opp_history_decisions[HISTORY], TURN,
				&my_credit, &opp_credit,
				&my_reward, &opp_reward,
				&my_punishment, &opp_punishment, &protocol_code);
		}
	}

	my_reward = 0;
	my_punishment = 1;
	opp_reward = 0;
	opp_punishment = 1;
	protocol_code = _100;
	// ��������, �����ֵ���ʷֻ��Ϊ��������һӡ��, 
	// ��˫���������ֽ��ʹӱ��ֿ�ʼ���¼���
	my_credit = 0.7;
	// "���Լ��ĵ���ˮ׼Ҫ�г�ֵ�����"

	/*	���Դ���: ���������������?
	*/
	std::cout << opp_credit << std::endl;

	// ���� 2: ���ݱ��ֶ�ս���ʵʱ����˫��������

	credit(my_decisions, opp_decisions, len,
		&my_credit, &opp_credit,
		&my_reward, &opp_reward,
		&my_punishment, &opp_punishment, &protocol_code);

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