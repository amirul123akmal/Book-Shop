#include "Basics.h"
#include "Menu.h"

// VST = visitor
class vst
{
private:
	sqlite3* db = NULL;
	sqlTable table{};
	sqlRow column{};
	sqlRow allCat{};
	sqlRow cart{};
	std::string command{};
private:
	void getAllCat();
	int buyPrompt();

public:
	// Constructor & De-Constructor
	vst();
	~vst();
public:
	// CALLBACK from sqlite3_exec
	// Func for claim data into this class locally
	int callbackClass(void* data, int argc, char** argv, char** colName);
	int getRow(void* data, int argc, char** argv, char** colName);
public:
	//Public Func for usage in `Shop.cpp`
	int displayAllItem();
};