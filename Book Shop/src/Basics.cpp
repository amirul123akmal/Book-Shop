#include <Basics.h>

namespace basic
{
	static void change(int a)
	{
		switch (a)
		{
		case 1:
			printf("\033[0;30m");
			break;
		case 2:
			printf("\033[0;31m");
			break;
		case 3:
			printf("\033[0;32m");
			break;
		case 4:
			printf("\033[0;33m");
			break;
		case 5:
			printf("\033[0;34m");
			break;
		case 6:
			printf("\033[0;35m");
			break;
		case 7:
			printf("\033[0;36m");
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
		printf("\033[0;0m");
	}
}