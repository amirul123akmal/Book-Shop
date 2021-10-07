#include "Basics.h"
#include "Book.h"

namespace shop
{
	static sqlite3* db = NULL;
	void init()
	{
		sqlite3_open("shop.db", &db);
	}
	void run()
	{

	}
}