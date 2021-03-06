#include "Functionality.h"

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
	case 5:
		// For exit only
		flag = true;
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
	sqlite3_close(db);
}
void sql::getTableData(const std::string& tableName)
{
	table.clear();
	command = "SELECT  *  FROM " + tableName + " ;";
	sqlite3_exec(db, command.c_str(), callback, ENABLED_STORE, NULL);
}
void sql::getData(const std::string& cmd)
{
	table.clear();
	sqlite3_exec(db, cmd.c_str(), callback, ENABLED_STORE, NULL);
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
	menu::EnterProgram();
	std::getline(std::cin, choices);
	if (choices == "")
		return 1000;
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
	command = "SELECT * FROM login WHERE name = " + basic::quoting(name) +" and pass = " + basic::quoting(pass) + ";";
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
	if (choices == "5")
		return switches;
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
		+basic::quoting(std::to_string(id)) + ","
		+ basic::quoting(name) + ");";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);

	// Create table for each category
	command = "CREATE TABLE " 
		+ basic::quoting(name) + 
		"("
		"id INT PRIMARY KEY NOT NULL,"
		"name TEXT NOT NULL,"
		"quantity INT NOT NULL,"
		"price FLOAT NOT NULL"
		");";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
}
int sql::editCat()
{
	std::string alterTable{};
	here:
	basic::clear();
	getTableData("categories");
	basic::printTable(table);
	menu::editCat();
	std::getline(std::cin, user);
	if (user == "3")
		return 1;
	basic::printColor("\nWhich Category do you want to change : ", 2);
	std::getline(std::cin, alterTable);
	switch (std::stoi(user))
	{
	case 1:
		changeCatName(alterTable);
		break;
	case 2:
		editCatData(alterTable);
		break;
	default:
		break;
	}
	goto here;
	
}
int sql::delCat()
{
	basic::clear();
	basic::printTable(table);
	basic::printColor("\nEnter 'aaa' to exit", 11);
	basic::printColor("\nWhich category do you want to remove : ", 2);
	std::getline(std::cin, user);
	if (user == "aaa")
		return 0;
	basic::printColor("\nAre you sure you want to continue (y/n) : ", 8);
	std::getline(std::cin, name);
	if (name == "n")
		return 0;
	command = "DELETE FROM categories WHERE category = "
		+ basic::quoting(user)  + ";";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
	command = "DROP TABLE "+
		basic::quoting(user) + ";";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
	return 1;
}

int sql::changeCatName(const std::string& whichTable)
{
	basic::clear();
	basic::printColor("\nTable that you want to change name : "+whichTable, 10);
	basic::printColor("\nEnter 'aaa' at input to exit", 4);
	basic::printColor("\nNew Name: ", 2);
	std::getline(std::cin, pass);
	if (pass == "aaa")
		return 0;
	command = "UPDATE categories SET category = "
		+ basic::quoting(pass) + " WHERE category = "
		+ basic::quoting(whichTable) + ";";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
	command = "ALTER TABLE "
		+ basic::quoting(whichTable) + " RENAME TO "
		+ basic::quoting(pass) + ";";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
	return 1;
}
int sql::editCatData(const std::string& whichTable)
{
	home:
	basic::clear();
	getTableData(whichTable);
	basic::printTable(table);
	menu::editDataTable();
	std::getline(std::cin, user);
	if (user == "5")
		return 0;
	basic::clear();
	basic::printTable(table);
	switch (std::stoi(user))
	{
	case 1:
		addData(whichTable);
		break;
	case 2:
		dataChangeName(whichTable);
		break;
	case 3:
		dataChangeQuantity(whichTable);
		break;
	case 4:
		dataDel(whichTable);
		break;
	}
	goto home;
	return 1;

}

int sql::addData(const std::string& leTable)
{
	// Field:
	// ID, name, quantity, price
	basic::clear();
	basic::printColor("You chose table: "+leTable, 8);
	std::string uName{}, uQuan{}, uPrice{};
	menu::addDataField();
	id = farthestID();
	basic::printColor("\nName: ", 2);
	std::getline(std::cin, uName);
	basic::printColor("Quantity: ", 2);
	std::getline(std::cin, uQuan);
	basic::printColor("Price: ", 2);
	std::getline(std::cin, uPrice);
	if (uName == "aaa" || uQuan == "aaa" || uPrice == "aaa")
		return 0;
	command = "INSERT INTO "
		+ basic::quoting(leTable) + " VALUES("
		+ basic::quoting(std::to_string(++id)) +","
		+ basic::quoting(uName) + ","
		+ basic::quoting(uQuan) + ","
		+ basic::quoting(uPrice) + ");"
		;
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
	return 1;
}
int sql::dataChangeName(const std::string& whichTable)
{
	menu::reqIdwithExit();
	std::getline(std::cin, pass);
	if (pass == "aaa")
		return 0;
	basic::printColor("\nPlease enter the new name: ", 2);
	std::getline(std::cin, user);
	command = "UPDATE "
		+ basic::quoting(whichTable) + " SET name = "
		+ basic::quoting(user) + " WHERE id = "
		+ basic::quoting(pass) + ";";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
	return 1;
}
int sql::dataChangeQuantity(const std::string& leTable)
{
	menu::reqIdwithExit();
	std::getline(std::cin, pass);
	if (pass == "aaa")
		return 0;
	basic::printColor("\nPlease enter the new quantity : ", 2);
	std::getline(std::cin, name);
	command = "UPDATE "
		+ basic::quoting(leTable) + " SET quantity = "
		+ basic::quoting(name) + " WHERE id = "
		+ basic::quoting(pass) + ";";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
	return 0;
}
int sql::dataDel(const std::string& leTable)
{
	menu::reqIdwithExit();
	std::getline(std::cin, pass);
	basic::printColor("Are you sure you want to continue (y/n) : ", 8);
	std::getline(std::cin, name);
	if (name == "n")
		return 0;
	command = "DELETE FROM "
		+ basic::quoting(leTable) + " WHERE id = "
		+ basic::quoting(pass) + ";";
	sqlite3_exec(db, command.c_str(), callback, NULL, NULL);
	return 1;
}