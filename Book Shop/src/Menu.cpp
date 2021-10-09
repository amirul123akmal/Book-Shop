#include "Menu.h"

namespace menu
{
	void EnterProgram()
	{
		basic::printColor("Welcome to UiTM Book Shop's\n", 11);
		basic::printColor("1. Buy\n", 2);
		basic::printColor("2. Admin Login\n", 2);
	}

	void editCat()
	{
		basic::printColor("\n1. Change Category Name", 4);
		basic::printColor("\n2. Edit Data", 4);
		basic::printColor("\n3. Exit", 10);
		basic::printColor("\n: ", 10);
	}

	void addDataField()
	{
		basic::printColor("Enter 'aaa' in any of these to exit this case", 13);
		basic::printColor("\nYou'll need to enter: ", 12);
		basic::printColor("\n1. Name of the items"
						  "\n2. Quantity of the iem"
						  "\n3. Price of the item", 11);
	}

	void editDataTable()
	{
		basic::printColor("\n1. Edit Data Name", 11);
		basic::printColor("\n2. Edit Quantity", 11);
		basic::printColor("\n3. Delete Row", 8);
		basic::printColor("\n4. Exit", 10);
		basic::printColor("\nChoices : ", 9);
	}	
}