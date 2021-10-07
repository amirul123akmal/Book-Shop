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
				switch (manage.adminMenu())
				{
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				default:
					break;
				}
				break;
			case 2:
				goto restart;
			}
			break;
		default:
			goto restart;
		}
	}
}