#include <iostream>
#include <string>
#include <vector>

#include <stdio.h>

#include <sqlite3.h>

#define CONSOLE(x) std::cout << x << std::endl
#define LOG(x) std::cout << x

namespace basic
{
	void clear();
	void stop();

	/// <summary>
	/// 1 = RED
	/// 2 = GREEN
	/// 3 = YELLOW
	/// 4 = BLUE
	/// 5 = MAGENTA
	/// 6 = CYAN
	/// 7 = WHITE
	/// </summary>
	/// <param name="sentences"></param>
	/// <param name="color"></param>
	void printColor(std::string sentences, int color);
}