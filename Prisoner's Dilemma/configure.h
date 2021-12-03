#pragma once
#ifndef GAME_CONFIGURE_H
#define GAME_CONFIGURE_H

//
#define HISTORY_LENGTH 20

// 轮数，每轮两两见面一次
#define MAX_ROUND 8

// 每轮见面一次，每次见面时博弈的局数
#define MAX_TURN 25


// 决策枚举
enum Decision {
	COOPERATION = 'c',
	BETRAYAL = 'b',
};


/**
*  玩家策略函数接口
*
*  本轮对战数据：
*  rs: 已完成的轮数
*  len: 已对抗的局数
*  my_id: 自己的id
*  my_decisions: 自己的决策历史
*  opp_id: 对手的id
*  opp_decisions: 对手的决策历史
*  repay: 本轮每局博弈时，背叛或者合作的代价和奖励
*
*  历史数据：
*  opp_history_decisions: 对手历史对战中采取的策略
*  opp_opp_history_decisions: 对手的对手采用的策略，不提供id，匿名
*
*/

enum Decision DEFAULT(int rs, int len, int my_id, const char my_decisions[], int opp_id, const char opp_decisions[], const int repay[MAX_TURN][4], const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN], const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN]);
enum Decision PROTOTYPE(int rs, int len, int my_id, const char my_decisions[], int opp_id, const char opp_decisions[], const int repay[MAX_TURN][4], const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN], const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN]);
enum Decision g00_naive(int rs, int len, int my_id, const char my_decisions[], int opp_id, const char opp_decisions[], const int repay[MAX_TURN][4], const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN], const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN]);
enum Decision g00_tricker(int rs, int len, int my_id, const char my_decisions[], int opp_id, const char opp_decisions[], const int repay[MAX_TURN][4], const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN], const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN]);
enum Decision g00_philosopher(int rs, int len, int my_id, const char my_decisions[], int opp_id, const char opp_decisions[], const int repay[MAX_TURN][4], const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN], const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN]);
enum Decision g00_stubborn(int rs, int len, int my_id, const char my_decisions[], int opp_id, const char opp_decisions[], const int repay[MAX_TURN][4], const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN], const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN]);
enum Decision g00_imitator(int rs, int len, int my_id, const char my_decisions[], int opp_id, const char opp_decisions[], const int repay[MAX_TURN][4], const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN], const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN]);
enum Decision gXX_YYYY(int rs, int len, int my_id, const char my_decisions[], int opp_id, const char opp_decisions[], const int repay[MAX_TURN][4], const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN], const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN]);

#endif
