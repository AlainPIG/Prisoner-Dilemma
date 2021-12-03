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

	// 信誉系统部分
	static const double LAUNCHER = 0.5, RECEIVER = 0.2, BETRAYER = 0.1;
	//  --------------------------------
	//  |  LAUNCHER  |     发起奖励     |
	//  |  RECEIVER  |     接受奖励     |
	//  |  BETRAYER  |   背叛惩罚系数   |
	//  --------------------------------
	static double my_credit = 0.8, opp_credit = 0.8;	// 双方信誉分
	static enum { _100, _101, _302 } protocol_code = _100;	// 协议代码
	// 下面语句定义了每局双方的信誉奖励值和惩罚系数
	//		如果加上 static 关键字, 则代表奖惩会不断继承到接下来的回合
	//		如果不加, 则代表不考虑玩家之前信用表现对当前回合的影响
	static double my_reward = 0, my_punishment = 1,
		opp_reward = 0, opp_punishment = 1;
	static const double decay = 0.9;
	//  --------------------------------
	//  |    reward    |     奖励值     |
	//  |  punishment  |    惩罚系数    |
	//  |    decay     |    衰减系数    |
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
			// 这里的设计是: 
			// 即便双方处于拒绝协议状态, 也有一定的自然几率自发地启动协议
			// (当然这自然几率是随局数衰减的, 因此要合作趁早)
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

	// 决策系统部分
	static const double probability_power = 0.5;
	// 根据对方信誉分计算概率
	double probability = pow(opp_credit, probability_power);

	// 生成 0~1 之间均匀分布的随机数
	double random_number;
	static int seed_number = 52;
	// seed_number 是为了让随机引擎输出的值具备随机性设立的一个 "种子数"
	// 原则上它的值可以任意选取

	std::default_random_engine engine;
	unsigned int time_now = time(NULL);
	engine.seed(time_now + seed_number);
	// 选取 "当前时刻 + 种子数" 为伪随机数的生成初始值
	std::uniform_real_distribution<double> get_random_number(0, 1);
	random_number = get_random_number(engine);
	/*	测试代码, 用于检查随机性
	std::cout << random_number << std::endl;
	*/
	seed_number += 4;
	// 每次必须改变一下 seed_number 的值以保证随机性

	// 开始决策
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