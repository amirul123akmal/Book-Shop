#include "Customer.h"

// Special way move data from callback to sql class
// start
// link to the forum: http://www.cplusplus.com/forum/beginner/278102/#msg1200491
int callBack(void* link, int numCols, char** rowData, char** colName)
{
	return reinterpret_cast<vst*>(link)->callbackClass(NULL, numCols, rowData, colName);
}
int vst::callbackClass(void* data, int argc, char** argv, char** colName)
{
	column.clear();
	for (int i = 0; i < argc; i++)
	{
		column.push_back(argv[i]);
	}
	table.push_back(column);
	return 0;
}
//end

vst::vst()
{
	sqlite3_open("shop.db", &db);
}
vst::~vst()
{
	sqlite3_close(db);
}

void vst::getAllCat()
{
	allCat.clear();
	for (int i = 0 ;i < table.size() ; i++)
	{
		allCat.push_back(table[i][1]);
	}
}

int vst::displayAllItem()
{
	basic::clear();
	command = "SELECT * FROM  categories;";
	sqlite3_exec(db, command.c_str(), callBack, ENABLED_STORE, NULL);
	getAllCat();
	for (int i = 0 ; i < allCat.size() ; i++)
	{
		table.clear();
		basic::printColor("Category : "+allCat[i] + "\n", 12);
		command = "SELECT * FROM "
			+ basic::quoting(allCat[i]) + ";";
		sqlite3_exec(db, command.c_str(), callBack,ENABLED_STORE, NULL);
		basic::printTable(table);
		CONSOLE("\n");
	}
	buyPrompt();
	basic::stop();
	return 1;
}

int vst::buyPrompt()
{
	std::string chooseCat{}, chooseId{}, count{}, user{};
	cart.clear();
	table.clear();
	buy_again:
	basic::printColor("Please Enter Which Category You Want : ", 9);
	std::getline(std::cin, chooseCat);
	if (chooseCat == "aaa" || chooseCat == "")
		return 0;
	basic::printColor("Please Enter the ID of the Category You Want : ", 9);
	std::getline(std::cin, chooseId);
	if (chooseId == "aaa" || chooseId == "")
		return 0;
	basic::printColor("How many do you want to buy (Please dont exceed from the remaining) : ", 9);
	std::getline(std::cin, count);
	if (count == "aaa" || count == "")
		return 0;
	command = "SELECT * FROM "
		+ basic::quoting(chooseCat) + " WHERE id = "
		+ basic::quoting(chooseId);
}