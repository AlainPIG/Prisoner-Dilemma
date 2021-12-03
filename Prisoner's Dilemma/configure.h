#pragma once
#ifndef GAME_CONFIGURE_H
#define GAME_CONFIGURE_H

//
#define HISTORY_LENGTH 20

// ������ÿ����������һ��
#define MAX_ROUND 8

// ÿ�ּ���һ�Σ�ÿ�μ���ʱ���ĵľ���
#define MAX_TURN 25


// ����ö��
enum Decision {
	COOPERATION = 'c',
	BETRAYAL = 'b',
};


/**
*  ��Ҳ��Ժ����ӿ�
*
*  ���ֶ�ս���ݣ�
*  rs: ����ɵ�����
*  len: �ѶԿ��ľ���
*  my_id: �Լ���id
*  my_decisions: �Լ��ľ�����ʷ
*  opp_id: ���ֵ�id
*  opp_decisions: ���ֵľ�����ʷ
*  repay: ����ÿ�ֲ���ʱ�����ѻ��ߺ����Ĵ��ۺͽ���
*
*  ��ʷ���ݣ�
*  opp_history_decisions: ������ʷ��ս�в�ȡ�Ĳ���
*  opp_opp_history_decisions: ���ֵĶ��ֲ��õĲ��ԣ����ṩid������
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
