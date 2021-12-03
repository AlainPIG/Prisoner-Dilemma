#include<iostream>
#include<math.h>
#include<random>
#include<time.h>

#include"configure.h"
#include"protocol.h"

enum Decision MODEL(int rs,
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
	//
	// 这一部分的程序将封装在 credit.cpp 中
	double my_credit = 0.95, opp_credit = 0.95;	// 双方初始信誉分
	protocol_code protocol_c = _100;	// 协议代码
	// 下面语句定义了每局双方的信誉奖励值和惩罚系数
	//		如果加上 static 关键字, 则代表奖惩会不断继承到接下来的回合
	//		如果不加, 则代表不考虑玩家之前信用表现对当前回合的影响
	double my_reward = 0, my_punishment = 1,
		opp_reward = 0, opp_punishment = 1;
	bool is_forgotten = false;
	//  --------------------------------
	//  |    reward    |     奖励值     |
	//  |  punishment  |    惩罚系数    |
	//  --------------------------------

	// 步骤 1: 根据信誉规则和历史记录初始化对方信誉分
	for (size_t HISTORY = 0; HISTORY < HISTORY_LENGTH; ++HISTORY) {
		credit(opp_opp_history_decisions[HISTORY],
			opp_history_decisions[HISTORY], MAX_TURN - 1,
			&my_credit, &opp_credit,
			&my_reward, &opp_reward,
			&my_punishment, &opp_punishment, &protocol_c, &is_forgotten, true);
		update(&my_credit, &opp_credit,
			&my_reward, &opp_reward,
			&my_punishment, &opp_punishment, &is_forgotten);
	}
	
	// 既往不咎, 看对手的历史只是为了留个第一印象, 
	// 对双方的信誉分奖惩从本轮开始重新计算
	my_credit = 0.7;
	// "对自己的道德水准要有充分的信心"

	/*	测试代码: 看看别人信誉如何?
	*/
//	if(len == 0) std::cout << opp_credit << std::endl;
	/*
	// 步骤 2: 根据本轮对战情况实时计算双方信誉分
	
	credit(my_decisions, opp_decisions, len,
		&my_credit, &opp_credit,
		&my_reward, &opp_reward,
		&my_punishment, &opp_punishment, &protocol_c);
	*/

	// **********************************************************
	// **********************************************************

	// 决策系统部分
	credit(my_decisions, opp_decisions, len,
		&my_credit, &opp_credit,
		&my_reward, &opp_reward,
		&my_punishment, &opp_punishment, &protocol_c, &is_forgotten, false);
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
		switch (protocol_c) {
		case _100:
			return Decision::COOPERATION;
			break;
		case _101:
			if (my_decisions[len - 1] == 'c') {
				return Decision::BETRAYAL;
			}
			else {
				if (probability > THRESHOLD || random_number < probability) {
					return Decision::COOPERATION;
				}
				else {
					return Decision::BETRAYAL;
				}
			}
			break;
		case _302:
			return Decision::BETRAYAL;
		}
	}

}