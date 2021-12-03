#pragma once
#ifndef PROTOCOL_H
#define PROTOCOL_H


#define LAUNCHER 0.8
#define RECEIVER 0.4
#define BETRAYER 0.1
#define DECAY 0.1

//  --------------------------------
//  |  LAUNCHER  |     ������     |
//  |  RECEIVER  |     ���ܽ���     |
//  |  BETRAYER  |   ���ѳͷ�ϵ��   |
//  |   DECAY    |     ˥��ϵ��     |
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
	enum protocol_code* protocol_code);

#endif