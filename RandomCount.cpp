#include "RandomCount.h"

char* GetRandomCount(int CycleTime)
{	
	char c;
	char RamdomStr[8];

	for (int i = 0; i < CycleTime; i++)
	{
		srand(time(NULL));		//设置随机数种子
		c = rand() % 52;
		if (c > 25)
			c = c - 25 + 'a';
		else
			c = c + 'A';
		RamdomStr[i] = c;
	}
	return RamdomStr;
}