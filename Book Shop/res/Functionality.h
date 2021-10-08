#include "Basics.h"

class sql
{
	
	// Start Private Member
private:
	sqlite3* db = NULL;
	sqlite3_stmt* execution = NULL;
	std::vector<std::string> column{};
	std::vector < std::vector < std::string >> table{};
	std::string command = "";
	std::string choices{};
	std::string name{}, pass{};
private:
	int col = 0;
	int counter = 0;
private:
	void getData();
	void getTableData(const std::string& tableName);
	int farthestID();
	bool intSwitch(const int& user);

	// Start Public Member
public:
	// All login related
	int adminLogin();
public:
	// All function for the menu related
	bool allCat();
	void editCat();
	void addCat();
	void delCat();
public:
	// All menu related
	int menu();
	int adminMenu();
	

	// Constructor
	sql();
	// Deconstructor
	~sql();
};