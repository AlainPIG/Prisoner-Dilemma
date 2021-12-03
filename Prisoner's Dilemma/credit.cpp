#include"configure.h"
#include"protocol.h"
#include"iostream"

void credit(const char* my_decisions,
	const char* opp_decisions,
	int len,
	double* my_credit,
	double* opp_credit,
	double* my_reward,
	double* opp_reward,
	double* my_punishment,
	double* opp_punishment,
	enum protocol_code* protocol_code)
{
	if (my_decisions[0] == 'm') {
		if (opp_decisions[0] == 'm') {
			return;
		}
		else {
			/*
				������
			*/
			return;
		}
	}
	else {
		if (opp_decisions[0] == 'm') {
			/*
				������
			*/
			return;
		}
		else {
			if (len == 1) {
				if (opp_decisions[0] == 'c') {
					*opp_reward = LAUNCHER;
					if (my_decisions[0] == 'b') {
						*protocol_code = _101;
					}
					else {
						*my_reward = LAUNCHER;
						*protocol_code = _100;
					}
				}
				else {
					if (my_decisions[0] == 'b') {
						*protocol_code = _302;
					}
					else {
						*my_reward = LAUNCHER;
						*protocol_code = _101;
					}
				}
			}
			else if (len >= 2) {
				switch (*protocol_code) {
				case _101:
					if (my_decisions[len - 2] == 'c') {
						if (opp_decisions[len - 1] == 'b') {
							*protocol_code = _302;
						}
						else {
							*opp_reward = RECEIVER;
							*protocol_code = _100;
						}
					}
					else {
						if (my_decisions[len - 1] == 'b') {
							*protocol_code = _302;
						}
						else {
							*my_reward = RECEIVER;
							*protocol_code = _100;
						}
					}
					break;
				case _100:
					if (my_decisions[len - 1] == 'b') {
						*my_punishment = BETRAYER;
						*protocol_code = _302;
					}
					if (opp_decisions[len - 1] == 'b') {
						*opp_punishment = BETRAYER;
						*protocol_code = _302;
					}
					break;
				case _302:
					if (opp_decisions[len - 1] == 'c') {
						*opp_reward = LAUNCHER;
						if (my_decisions[len - 1] == 'b') {
							*protocol_code = _101;
						}
						else {
							*my_reward = LAUNCHER;
							*protocol_code = _100;
						}
					}
					else {
						if (my_decisions[len - 1] == 'c') {
							*my_reward = LAUNCHER;
							*protocol_code = _101;
						}
					}
					// ����������:
					// ����˫�����ھܾ�Э��״̬, Ҳ��һ������Ȼ�����Է�������Э��
					// (��Ȼ����Ȼ�����������˥����, ���Ҫ��������)
				}
			}
			*my_credit = (*my_credit + *my_reward) * (*my_punishment) * DECAY;
			*opp_credit = (*opp_credit + *opp_reward) * (*opp_punishment) * DECAY;
			if (*my_credit > 1) {
				*my_credit = 1;
			}
			if (*opp_credit > 1) {
				*opp_credit = 1;
			}
		}
		return;
	}
}
