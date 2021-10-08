#include "Basics.h"

namespace basic
{
	static void change(int a)
	{
		switch (a)
		{
		case 1:
			printf("\033[0;31m");
			break;
		case 2:
			printf("\033[0;32m");
			break;
		case 3:
			printf("\033[0;33m");
			break;
		case 4:
			printf("\033[0;34m");
			break;
		case 5:
			printf("\033[0;35m");
			break;
		case 6:
			printf("\033[0;36m");
			break;
		case 7:
			printf("\033[0;37m");
			break;
		case 8:
			printf("\033[31;1m");
			break;
		case 9:
			printf("\033[32;1m");
			break;
		case 10:
			printf("\033[33;1m");
			break;
		case 11:
			printf("\033[34;1m");
			break;
		case 12:
			printf("\033[35;1m");
			break;
		case 13:
			printf("\033[36;1m");
			break;
		case 14:
			printf("\033[37;1m");
			break;
		default:
			break;
		}
	}
	void clear()
	{
		system("cls");
	}
	void stop()
	{
		printf("\n");
		system("pause");
	}
	void printColor(std::string sentences, int color)
	{
		change(color);
		printf("%s", sentences.c_str());
		// reset
		printf("\033[0;37m");
	}
	void printTable(const std::vector<std::vector<std::string>>& theTable)
	{
		for (int i = 0 ; i < theTable.size() ; i++)
		{
			for (int j = 0 ; j < theTable[i].size() ; j++)
			{
				printColor(" " + theTable[i][j], j + 4);
			}
			CONSOLE("");
		}
	}
}