#include "Basics.h"

class sql
{
	// Start Private Member
private:
	sqlite3* db = NULL;
	sqlite3_stmt* execution = NULL;
	std::string command = "";
	std::string choices{};
	std::string name{}, pass{};
	std::vector<std::string> column{};
	std::vector < std::vector < std::string >> table{};
	std::string user{};
private:
	int id = 0;
private:
	/// <summary>
	/// SELECT data based from custom command
	/// </summary>
	/// <param name="cmd"></param>
	void getData(const std::string& cmd);

	/// <summary>
	/// <para>Insert table name</para>
	/// <para>This function will collect whole data and insert in table</para>
	/// </summary>
	/// <param name="tableName"></param>
	void getTableData(const std::string& tableName);
	/// <summary>
	/// Get the farthest ID in table
	/// </summary>
	/// <returns></returns>
	int farthestID();
	bool intSwitch(const int& user);

	// Start Public Member
public:
	// Get data from SQL CALLBACK
	
	/// <summary>
	/// <para>data = unused ( for reserve )</para>
	/// <para>argc = How many data in that row (type - int) </para>
	/// <para>argv = The data in that row (type - array) </para>
	/// <para>colname = Name of that Column (type - array)</para>
	/// </summary>
	/// <param name="data"></param>
	/// <param name="argc"></param>
	/// <param name="argv"></param>
	/// <param name=""></param>
	/// <returns></returns>
	int callbackClass(void* data, int argc, char** argv, char** colName);

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