#include<iostream>
#include<math.h>
#include<random>
#include<time.h>
#include"configure.h"

enum Decision FINAL(int rs,
	int len,
	int my_id,
	const char* my_decisions,
	int opp_id,
	const char* opp_decisions,
	const int repay[MAX_TURN][4],
	const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN],
	const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN])
{
	//DEFINITION OF IMPORTANT PARAMETERS
	const double LAUNCHER = 0.3, RECEIVER = 0.2, BETRAYER = 0.1;
	const double DECAY = 0.98, THRESHOLD = 0.93, IDIOT = 0.98;
	const double INIT_VALUE = 0.8, BETA = 0.5;
	const int NAIVE_THRESHOLD = 400;
	enum PROTOCOL_TYPE {_100, _101, _302} cur_protocol = _100;
	const std::vector<int> PY_LIST = {};

	//INITIALIZATION OF RANDOM MODULE
	double rd;
	int seed_number = 101;
	for (int i = 0; i < rs + len + my_id + opp_id; i++) seed_number = (seed_number * seed_number + 5) % 10007;
	std::default_random_engine engine;
	unsigned int time_now = time(NULL);
	engine.seed(time_now + seed_number);
	std::uniform_real_distribution<double> get_random_number(0, 1);
	for(int i=0;i < rs + len + my_id + opp_id;i++) rd = get_random_number(engine);

	//CREDIT CALCULATION
	double opp_credit = INIT_VALUE, opp_reward = 0, opp_punishment = 1;
	int opp_naive = 0;
	for (int j = 0; j < HISTORY_LENGTH; j++) {
		opp_reward = 0, opp_punishment = 1;
		cur_protocol = _100;
		if (opp_history_decisions[j][0] == 'm' || opp_opp_history_decisions[j][0] == 'm')  continue;
		for (int i = 0; i < MAX_TURN; i++) {
			if (i == 0) {
				if (opp_history_decisions[j][0] == 'c') opp_reward = LAUNCHER;
				if (opp_history_decisions[j][0] == 'c' && opp_opp_history_decisions[j][0] == 'c') cur_protocol = _100;
				else if (opp_history_decisions[j][0] == 'c' || opp_opp_history_decisions[j][0] == 'c') cur_protocol = _101;
				else cur_protocol = _302;
			}
			else if (i == 1) {
				switch (cur_protocol) {
				case _101:
					if (opp_history_decisions[j][0] == 'c' && opp_opp_history_decisions[j][1] == 'c') {
						cur_protocol = _100;
						opp_reward = LAUNCHER;
					}
					else if (opp_history_decisions[j][1] == 'c' && opp_opp_history_decisions[j][0] == 'c') {
						cur_protocol = _100;
						opp_reward = RECEIVER;
					}
					else {
						cur_protocol = _302;
					}
					break;
				case _100:
					if (opp_opp_history_decisions[j][1] == 'b' || opp_history_decisions[j][1] == 'b') {
						cur_protocol = _302;
						if (opp_history_decisions[j][1] == 'b') opp_punishment = BETRAYER;
					}
					break;
				case _302:
					break;
				}
			}
			else {
				switch (cur_protocol) {
				case _100:
					if (opp_opp_history_decisions[j][i] == 'b' || opp_history_decisions[j][i] == 'b') {
						cur_protocol = _302;
						if (opp_history_decisions[j][i] == 'b') opp_punishment = BETRAYER;
					}
					break;
				case _302:
					if (opp_history_decisions[j][i] == 'c') opp_naive += i;
					break;
				}
			}
		}
		opp_credit = (opp_credit + opp_reward) * opp_punishment * DECAY;
	}

	//DECISION MAKING;
	for (int i = 0; i < PY_LIST.size(); i++) if (opp_id == PY_LIST[i]) return Decision::COOPERATION;
	cur_protocol = _100;
	for (int i = 0; i <= len; i++) {
		if (i == 0) {
			if (i == len) {
				if (opp_naive > NAIVE_THRESHOLD) return Decision::BETRAYAL;
				if (rd < pow(opp_credit, BETA) || pow(opp_credit, BETA) > THRESHOLD) return Decision::COOPERATION;
			}
			if (my_decisions[i] == 'c' && opp_decisions[i] == 'c') cur_protocol = _100;
			else if (my_decisions[i] == 'c' || opp_decisions[i] == 'c') cur_protocol = _101;
			else cur_protocol = _302;
		}
		else if (i == 1) {
			if (i == len) {
				if (opp_naive > NAIVE_THRESHOLD) return Decision::BETRAYAL;
				switch (cur_protocol) {
				case _100:
					return Decision::COOPERATION;
				case _101:
					if (my_decisions[0] == 'c') return Decision::BETRAYAL;
					else if (rd < pow(opp_credit, BETA) || pow(opp_credit, BETA) > THRESHOLD) return Decision::COOPERATION;
				case _302:
					return Decision::BETRAYAL;
				}
			}
			switch (cur_protocol) {
			case _100:
				if (opp_decisions[i] == 'b') cur_protocol = _302;
				break;
			case _101:
				if (my_decisions[0] == 'c' && opp_decisions[1] == 'c') cur_protocol = _100;
				else if (my_decisions[1] == 'c' && opp_decisions[0] == 'c') cur_protocol = _100;
				else cur_protocol = _302;
				break;
			case _302:
				break;
			}
		}
		else {
			switch (cur_protocol) {
			case _100:
				if (i == len) return Decision::COOPERATION;
				if (opp_decisions[i] == 'b') cur_protocol = _302;
				break;
			case _302:
				if (i == len) return Decision::BETRAYAL;
				break;
			}
		}
	}

	//DEFAULT
	return Decision::BETRAYAL;
}