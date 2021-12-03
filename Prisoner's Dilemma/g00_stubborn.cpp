#include <stdio.h>
#include "configure.h"

// 无视前面所有历史，只要被伤害一次，就永不合作
enum Decision g00_stubborn(	int rs, 
							int len,
							int my_id,
							const char *my_decisions,
							int opp_id,
							const char *opp_decisions ,
							const int repay[MAX_TURN][4],
							const char opp_history_decisions[HISTORY_LENGTH][MAX_TURN],
							const char opp_opp_history_decisions[HISTORY_LENGTH][MAX_TURN])
{
	//首选合作，如果被背叛过，则再也不会和你合作，哼
	bool isEnemy = false;

	//浏览此次交锋，看看前几次的交锋，你是否曾经背叛我
	for (int idx = 0; idx < len; idx++)
	{
		if (opp_decisions[idx] == BETRAYAL)
		{
			isEnemy = true;
			break;
		}
	}

	//我就是固执，背叛我的人就永不合作，再见！
	if (isEnemy)
	{
		return BETRAYAL;
	}
	else
	{
		return COOPERATION;
	}

}
