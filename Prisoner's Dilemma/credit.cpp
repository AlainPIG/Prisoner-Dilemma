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
	enum protocol_code* protocol_c,
	bool* is_forgotten,
	bool stat)
{
	*my_reward = 0;
	*my_punishment = 1;
	*opp_reward = 0;
	*opp_punishment = 1;
	// 每查看一轮对手的历史记录, 都将奖惩清空
	*protocol_c = _100;
	// 每查看一轮对手的历史记录, 默认协议代码为 "_100" 即 "握手"
	if (my_decisions[0] == 'm') {
		*is_forgotten = true;
		// 如果记录为 'm', 则标记为 "已遗忘"
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
	else if (opp_decisions[0] == 'm') {
			*is_forgotten = true;
			/*
				待补充
			*/
			return;
	}
	else {
		*is_forgotten = false;
		// 如果双方记录均未遗忘, 则开始根据记录计算奖惩
		for (int i = 0; i < len; i++) {
			if (i == 0) {
				if (opp_decisions[0] == 'c') {
					*opp_reward = LAUNCHER;
					if (my_decisions[0] == 'b') {
						*protocol_c = _101;
					}
					else {
						*my_reward = LAUNCHER;
						*protocol_c = _100;
					}
				}
				else {
					if (my_decisions[0] == 'b') {
						*protocol_c = _302;
						return;
					}
					else {
						*my_reward = LAUNCHER;
						*protocol_c = _101;
					}
				}
			}
			else if (i == 1) {
				switch (*protocol_c) {
				case _101:
					if (opp_decisions[0] == 'c' && my_decisions[1] == 'c') {
						*protocol_c = _100;
						*my_reward = RECEIVER;
						*opp_reward = LAUNCHER;
					}
					else if (opp_decisions[1] == 'c' && my_decisions[1] == 'c') {
						*protocol_c = _100;
						*my_reward = RECEIVER;
						*opp_reward = LAUNCHER;
					}
					else {
						*protocol_c = _302;
						return;
					}
					break;
				case _100:
					if (my_decisions[1] == 'b' || opp_decisions[1] == 'b') {
						*protocol_c = _302;
						if (my_decisions[1] == 'b') *my_punishment = BETRAYER;
						if (opp_decisions[1] == 'b') *opp_punishment = BETRAYER;
						return;
					}
				}
			}
			else if (i >= 2) {
				switch (*protocol_c) {
				case _101:				
					if (my_decisions[i] == 'b' || opp_decisions[i] == 'b') {
						*protocol_c = _302;
						if (my_decisions[i] == 'b') *my_punishment = BETRAYER;
						if (opp_decisions[i] == 'b') *opp_punishment = BETRAYER;
						return;
					}
					break;
				case _302:
					if (my_decisions[i] == 'c' || opp_decisions[i] == 'c') {
						if (my_decisions[i] == 'c') *my_punishment = IDIOT;
						if (opp_decisions[i] == 'c') *opp_punishment = IDIOT;
						return;
					}
				}

			}
		}
		return;
	}
}
void update(double* my_credit, double* opp_credit, double* my_reward, double* opp_reward, double* my_punishment, double* opp_punishment, bool* is_forgotten){
	if (*is_forgotten) return;
	*my_credit = (*my_credit + *my_reward) * (*my_punishment) * DECAY;
	*opp_credit = (*opp_credit + *opp_reward) * (*opp_punishment) * DECAY;
}