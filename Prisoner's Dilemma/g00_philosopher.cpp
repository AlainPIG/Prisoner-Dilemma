#include <time.h>
#include <stdlib.h>
#include "configure.h"

// 随机出牌
enum Decision g00_philosopher(	int rs, 
								int len,
								int my_id,
								const char* my_decisions,
								int opp_id,
								const char* opp_decisions ,
								const int   repay[MAX_TURN][4],
								const char  opp_history_decisions[HISTORY_LENGTH][MAX_TURN],
								const char  opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN])
{

	srand((unsigned)time(NULL) + len);
	int r = rand();
	if (r % 2 == 0)
    {
		return COOPERATION;
	}
	else
	{
		return BETRAYAL;
	}
}
