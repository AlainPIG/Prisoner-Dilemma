#pragma once
#ifndef PROTOCOL_H
#define PROTOCOL_H


#define LAUNCHER 0.3
#define RECEIVER 0.2
#define BETRAYER 0.6
#define DECAY 0.98
#define THRESHOLD 0.93

//  --------------------------------
//  |  LAUNCHER  |     发起奖励     |
//  |  RECEIVER  |     接受奖励     |
//  |  BETRAYER  |   背叛惩罚系数   |
//  |   DECAY    |     衰减系数     |
//  --------------------------------


enum protocol_code { _100, _101, _302 };

void credit(const char* my_decisions,
	const char* opp_decisions,
	int len,
	double* my_credit,
	double* opp_credit,
	double* my_reward,
	double* opp_reward,
	double* my_punishment,
	double* opp_punishment,
	enum protocol_code* protocol_code,
	bool* is_forgotten,
	bool stat);

void update(double* my_credit, double* opp_credit, double* my_reward, double* opp_reward, double* my_punishment, double* opp_punishment, bool* is_forgotten);
#endif