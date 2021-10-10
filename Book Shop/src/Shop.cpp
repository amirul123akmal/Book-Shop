#include "Basics.h"
#include "Shop.h"
#include "Functionality.h"
#include "Customer.h"

namespace shop
{
	void run()
	{
		sql manage;
		vst cust;
	restart:
		switch (manage.menu())
		{
		case 1:
			// For Customers
			cust.displayAllItem();
			goto restart;
			break;
		case 2:
			// For Admin
			again:
			switch (manage.adminLogin())
			{
			case 0:
				goto again;
			case 1:
				// Credential Successfull
				switch (manage.adminMenu())
				{
				case 5:
					goto restart;
				}
				break;
			case 2:
				goto restart;
			}
			break;
		case 100:
			break;
		default:
			goto restart;
		}
	}
}