#include "Basics.h"

class sql
{
private:
	sqlite3* db = NULL;
	sqlite3_stmt* execution = NULL;
	std::string command = "";
	std::vector<std::string> column{};
	std::vector < std::vector < std::string >> table{};
	
private:
	int col = 0;
	int counter = 0;

private:
	void getData();
	void getTableData(const std::string& tableName);
public:
	sql();
	int menu();
	int adminLogin();
	int adminMenu();
	~sql();
};