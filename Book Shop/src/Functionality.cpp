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
		break;
	case 3:
		flag = true;
		addCat();
		break;
	case 4:
		flag = true;
		break;
	}
	return flag;
}

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
	command = "SELECT * FROM " + quoting(tableName) + ";";
	sqlite3_prepare(db, command.c_str(), -1, &execution, NULL);
	sqlite3_step(execution);
	col = sqlite3_column_count(execution);
	counter = 0;
	while (sqlite3_column_text(execution, counter++))
	{
		column.clear();
		for (int i = 0 ; i < col; i++)
		{
			column.push_back(std::string((char*)(sqlite3_column_text(execution, i))));
		}
		table.push_back(column);
		sqlite3_step(execution);
	}
}
void sql::getData()
{
	table.clear();
	counter = 0;
	column.clear();
	col = sqlite3_column_count(execution);
	while (sqlite3_column_text(execution, counter++))
	{
		column.clear();
		for (int i = 0; i < col; i++)
		{
			column.push_back(std::string((char*)(sqlite3_column_text(execution, i))));
		}
		table.push_back(column);
		sqlite3_step(execution);
	}
}

int sql::farthestID()
{
	int id = 0;
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
	sqlite3_prepare(db, command.c_str(), -1, &execution, NULL);
	sqlite3_step(execution);
	getData();
	if (counter == 1) 
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
	int id = farthestID();
	id++;
	command = "INSERT INTO categories VALUES("
		+quoting(std::to_string(id)) + ","
		+ quoting(name) + ");";
	sqlite3_prepare(db, command.c_str(), -1, &execution, NULL);
	sqlite3_step(execution);
}

void sql::editCat()
{

}

void sql::delCat()
{

}