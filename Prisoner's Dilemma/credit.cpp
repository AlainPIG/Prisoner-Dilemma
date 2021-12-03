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
				待补充
			*/
			return;
		}
	}
	else {
		if (opp_decisions[0] == 'm') {
			/*
				待补充
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
					// 这里的设计是:
					// 即便双方处于拒绝协议状态, 也有一定的自然几率自发地启动协议
					// (当然这自然几率是随局数衰减的, 因此要合作趁早)
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
