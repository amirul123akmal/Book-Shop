#include "Functionality.h"

std::string quoting(const std::string& sentence)
{
	return std::string("'") + sentence + std::string("'");
}
// intDependent = Internal Dependent
void intDependent(int start)
{
	basic::printColor("\n" + std::to_string(start++) + ". Edit Category\n", 11);
	basic::printColor(std::to_string(start++) + ". Add Category\n", 10);
	basic::printColor(std::to_string(start++) + ". Delete Category\n", 8);
}
bool sql::intSwitch(const int& user)
{
	bool flag = false;
	switch (user)
	{
	case 2:
		flag = true;
		editCat();
		break;
	case 3:
		flag = true;
		addCat();
		break;
	case 4:
		flag = true;
		delCat();
		break;
	}
	return flag;
}

// Special way move data from callback to sql class
// start
// link to the forum: http://www.cplusplus.com/forum/beginner/278102/#msg1200491
int callback(void* link, int numCols, char **rowData, char**colName)
{
	return reinterpret_cast<sql*>(link)->callbackClass(NULL, numCols, rowData, colName);
}
int sql::callbackClass(void* data, int argc, char** argv, char** colName)
{
	column.clear();
	for (int i = 0;i < argc ; i++)
	{
		column.push_back(argv[i]);
	}
	table.push_back(column);
	return 0;
}
//end

sql::sql()
{
	sqlite3_open("shop.db", &db);
}
sql::~sql()
{
	sqlite3_finalize(execution);
	sqlite3_close(db);
}
void sql::getTableData(const std::string& tableName)
{
	table.clear();
	command = "SELECT  *  FROM " + tableName + " ;";
	sqlite3_exec(db, command.c_str(), callback, reinterpret_cast<void*>(this), NULL);
}
void sql::getData(const std::string& cmd)
{
	table.clear();
	sqlite3_exec(db, cmd.c_str(), callback, reinterpret_cast<void*>(this), NULL);
}
int sql::farthestID()
{
	id = 0;
	for (int i = 0 ; i < table.size() ; i++)
	{
		id = std::stoi(table[i][0]);
	}
	return id;
}
int sql::menu()
{
	basic::clear();
	basic::printColor("Welcome to UiTM Book Shop's\n", 11);
	basic::printColor("1. Buy\n", 2);
	basic::printColor("2. Admin Login\n", 2);
	std::getline(std::cin, choices);
	return std::stoi(choices);
}
int sql::adminLogin()
{
	basic::clear();
	basic::printColor("Enter 'aaa' at both name and password to exit this login \n", 11);
	basic::printColor("Name: ", 2);
	std::getline(std::cin, name);
	basic::printColor("Pass: ", 2);
	std::getline(std::cin, pass);
	if (name == "aaa" && pass == "aaa")
	{
		return 2;
	}
	command = "SELECT * FROM login WHERE name = " + quoting(name) +" and pass = " + quoting(pass) + ";";
	getData(command);
	if (table.size() == 0) 
	{
		basic::printColor("The login Credential does not exist in database", 1);
		basic::stop();
		return 0;
	}
	basic::printColor("Access Granted", 2);
	basic::stop();
	return 1;

}
int sql::adminMenu()
{
	menu:
	basic::clear();
	basic::printColor("1. All Category", 11);
	intDependent(2);
	basic::printColor("5. Log Out\n", 13);
	printf(":");
	std::getline(std::cin, choices);
	int switches = std::stoi(choices);
	switch (switches)
	{
	case 1:
		if (allCat())
			goto menu;
		break;
	}
	if (intSwitch(switches))
		goto menu;
	return switches;
}
bool sql::allCat()
{
	basic::clear();
	getTableData("categories");
	basic::printTable(table);
	intDependent(1);
	basic::printColor("4. Exit\n", 13);
	printf(":");
	std::getline(std::cin, choices);
	return intSwitch(std::stoi(choices) + 1);
}
void sql::addCat()
{
	basic::clear();
	getTableData("categories"); // For refresh
	basic::printColor("Category Name:", 9);
	std::getline(std::cin, name);
	id = farthestID();
	id++;
	command = "INSERT INTO categories VALUES("
		+quoting(std::to_string(id)) + ","
		+ quoting(name) + ");";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);

	// Create table for each category
	command = "CREATE TABLE " 
		+ quoting(name) + 
		"("
		"id INT PRIMARY KEY NOT NULL,"
		"name TEXT NOT NULL,"
		"quantity INT NOT NULL,"
		"price FLOAT NOT NULL"
		");";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
}
void sql::editCat()
{
	basic::clear();
	getTableData("categories");
	basic::printTable(table);
	basic::printColor("\nYou may only update the name only", 4);
	basic::printColor("\nPlease select the ID that you want to change: ", 2);
	std::getline(std::cin, name);
	basic::printColor("\nNew Name: ", 2);
	std::getline(std::cin, pass);
	id = std::stoi(name);
	user = table[id-1][1]; // save old name
	command = "UPDATE categories SET category = " 
		+ quoting(pass) + " WHERE id = "
		+ quoting(name) + ";";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
	command = "ALTER TABLE "
		+ quoting(user) + " RENAME TO " 
		+ quoting(pass) + ";";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
}

void sql::delCat()
{

}