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
	/// <para> 1 = RED      8 = BRIGHT RED      </para>
	/// <para> 2 = GREEN    9 = BRIGHT GREEN	</para>
	/// <para> 3 = YELLOW   10= BRIGHT YELLOW	</para>
	/// <para> 4 = BLUE     11= BRIGHT BLUE		</para>
	/// <para> 5 = MAGENTA  12= BRIGHT MAGENTA	</para>
	/// <para> 6 = CYAN     13= BRIGHT CYAN		</para>
	/// <para> 7 = WHITE	14= BRIGHT WHITE	</para>
	/// </summary>
	/// <param name="sentences"></param>
	/// <param name="color"></param>
	void printColor(std::string sentences, int color);

	void printTable(const std::vector<std::vector<std::string>>& theTable);

	std::string quoting(const std::string& sentence);
}