#include "Basics.h"
#include "Shop.h"
#include "Functionality.h"

namespace shop
{
	void run()
	{
		sql manage;
	restart:
		switch (manage.menu())
		{
		case 1:
			break;
		case 2:
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
					goto again;
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