#include <stdio.h>
#include "configure.h"

// ����ǰ��������ʷ��ֻҪ���˺�һ�Σ�����������
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
	//��ѡ��������������ѹ�������Ҳ��������������
	bool isEnemy = false;

	//����˴ν��棬����ǰ���εĽ��棬���Ƿ�����������
	for (int idx = 0; idx < len; idx++)
	{
		if (opp_decisions[idx] == BETRAYAL)
		{
			isEnemy = true;
			break;
		}
	}

	//�Ҿ��ǹ�ִ�������ҵ��˾������������ټ���
	if (isEnemy)
	{
		return BETRAYAL;
	}
	else
	{
		return COOPERATION;
	}

}
