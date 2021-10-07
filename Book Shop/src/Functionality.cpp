#include "Functionality.h"

std::string quoting(std::string& sentence)
{
	return std::string("'") + sentence + std::string("'");
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
	command = "SELECT * FROM " + tableName + ";";
	sqlite3_prepare(db, command.c_str(), -1, &execution, NULL);
	sqlite3_step(execution);
	col = sqlite3_column_count(execution);
	counter = 0;
	while (sqlite3_column_text(execution, counter++))
	{
		column.clear();
		for (int i = 0 ; i < col; i++)
		{
			column.push_back(std::string((char*)sqlite3_column_text(execution, i)));
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
int sql::menu()
{
	std::string answer{};
	basic::clear();
	std::cin.ignore();
	CONSOLE("Welcome to UiTM Book Shops'\n");
	CONSOLE("1. Buy");
	CONSOLE("2. Admin Login");
	std::getline(std::cin, answer);
	return std::stoi(answer);
}
int sql::adminLogin()
{
	basic::clear();
	std::string name{}, pass{};
	std::cin.ignore();
	CONSOLE("Enter 'aaa' at both name and password to exit this login \n");
	LOG("Name: ");
	std::getline(std::cin, name);
	LOG("Pass: ");
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
		return 0;
	}
	basic::printColor("Access Granted", 2);
	return 1;

}
int sql::adminMenu()
{
	std::string choices{};
	basic::clear();
	basic::printColor("1. All Category\n", 11);
	basic::printColor("2. Add Category\n", 10);
	basic::printColor("3. Delete Category\n", 8);
	basic::printColor("4. Log Out\n", 13);
	printf(":");
	std::cin.ignore();
	std::getline(std::cin, choices);
	return std::stoi(choices);
}