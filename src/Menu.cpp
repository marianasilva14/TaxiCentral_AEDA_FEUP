#include "Menu.h"


using namespace std;

/******************************************
			Customer management
 ******************************************/

/**
 * Customers menu, where the user can choose what the option that wants
 * @param central Central taxis
 */
unsigned short int customersMenu(CentralTaxis &central)
{
	char chosenOption;

	cleanDisplay();

	do
	{
		cout << endl << endl;
		cout << TAB_BIG << "CUSTOMER MENU MANAGEMENT" << endl;
		cout << endl;
		cout << TAB << "1- Show information about all customers" << endl;
		cout << TAB << "2- Show information about all customers by type" << endl;
		cout << TAB << "3- Show information about one customer" << endl;
		cout << TAB << "4- Edit customers" << endl;
		cout << TAB << "5- Remove customers" << endl;
		cout << TAB << "6- Insert new customer" << endl;
		cout << TAB << "0- Back" << endl << endl;

		cout << "What is the option that you want? ";
		cin >> chosenOption;

		cleanDisplay();

		switch (chosenOption)
		{
		case '1':
			showAllCustomersInfo(central.getCustomers());
			break;

		case '2':
			customerMenuType(central);
			break;

		case '3':
			oneCustomerMenu(central);
			break;

		case '4':
			editCustomerMenu(central);
			break;

		case '5':
			central.removeCustomer();
			break;

		case '6':
			central.insertNewCustomer();
			break;

		case '0':
		{
			cleanDisplay();
			return 0;
		}
		default:
			cout << "Invalid option. Try again." << endl;
			break;
		}
	} while (chosenOption != '0');

	return 1;
}
/**
 * Customer type menu, where the user can search for private or company customers
 * @param central Central taxis
 */
unsigned short int customerMenuType(CentralTaxis &central)
{
	char chosenOption;

	do
	{
		cout << endl << endl;
		cout << TAB_BIG << "Show information by type:" << endl;
		cout << endl;
		cout << TAB << "1- Private Customers" << endl;
		cout << TAB << "2- Company Customers" << endl;
		cout << TAB << "0- Back" << endl << endl;

		cout << "What is the option that you want? ";
		cin >> chosenOption;

		char type;
		cleanDisplay();
		switch (chosenOption)
		{
		case '1':
			type = 'P';
			showAllCustomersInfoByType(central.getCustomers(), type);
			break;

		case '2':
			type = 'C';
			showAllCustomersInfoByType(central.getCustomers(), type);
			break;

		case '0':
		{
			cleanDisplay();
			return 0;
		}

		default:
			cout << "Invalid option. Try again." << endl;
			break;
		}
	} while (chosenOption != '0');

	return 1;
}

/**
 * Shows a customer's menu, where the user can search through the customer nif or through the customer name.
 * @param central Central taxis
 */
unsigned short int oneCustomerMenu(CentralTaxis &central)
{
	char chosenOption;

	do
	{
		cout << endl << endl;
		cout << TAB_BIG << "How do you want search?" << endl;
		cout << endl;
		cout << TAB << "1- Through NIF" << endl;
		cout << TAB << "2- Through name" << endl;
		cout << TAB << "0- Back" << endl << endl;

		cout << "What is the option that you want? ";
		cin >> chosenOption;

		cleanDisplay();
		switch (chosenOption)
		{
		case '1':
			showCustomersInfoByNif(central.getCustomers());
			break;

		case '2':
			showCustomersInfoByName(central.getCustomers());
			break;

		case '0':
		{
			cleanDisplay();
			return 0;
		}

		default:
			cout << "Invalid option. Try again." << endl;
			break;
		}
	} while (chosenOption != '0');

	return 1;
}

/**
 * Shows a edit customer's menu
 * @param central Central taxis
 */
unsigned short int editCustomerMenu(CentralTaxis &central)
{
	char chosenOption;
	do
	{
		cout << endl << endl;
		cout << TAB_BIG << "What do you want to change?" << endl;
		cout << endl;
		cout << TAB << "1- Name" << endl;
		cout << TAB << "2- Address" << endl;
		cout << TAB << "3- Phone Number" << endl;
		cout << TAB << "0- Back" << endl << endl;


		cout << "What is the option that you want? ";
		cin >> chosenOption;

		cleanDisplay();
		switch (chosenOption)
		{
		case '1':
			central.editCustomerName();
			break;

		case '2':
			central.editCustomerAddress();
			break;

		case '3':
			central.editCustomerPhoneNumber();
			break;

		case '0':
		{
			cleanDisplay();
			return 0;
		}

		default:
			cout << "Invalid option. Try again." << endl;
			break;
		}
	} while (chosenOption != '0');

	return 1;
}

/******************************************
			Service management
 ******************************************/

/**
 * Shows a customer service's menu, where the user can search through the customer nif or through the customer name.
 * @param central Central taxis
 */
unsigned short int oneCustomerServicesMenu(CentralTaxis &central)
{
	char chosenOption;

	do {
		cout << endl << endl;
		cout << TAB_BIG << "How do you want search?" << endl;
		cout << endl;
		cout << TAB << "1- Through NIF" << endl;
		cout << TAB << "2- Through name" << endl;
		cout << TAB << "0- Back" << endl << endl;

		cout << "What is the option that you want? ";
		cin >> chosenOption;

		cleanDisplay();
		switch (chosenOption)
		{
		case '1':
			showCustomerServicesByNif(central.getServices(), central.getCustomers());
			break;

		case '2':
			showCustomerServicesByName(central.getServices(), central.getCustomers());
			break;

		case '0':
		{
			cleanDisplay();
			return 0;
		}

		default:
			cout << "Invalid option. Try again." << endl;
			break;
		}
	} while (chosenOption != '0');

	return 1;
}

/**
 * Shows the services menu
 * @param central Central taxis
 */
unsigned short int servicesMenu(CentralTaxis &central)
{
	char chosenOption;

	/*Menu of services, where the user can choose what the option that wants*/
	cleanDisplay();

	do{
		cout << endl << endl;
		cout << TAB_BIG << "SERVICE MENU MANAGEMENT" << endl;
		cout << endl;
		cout << TAB << "1- Show information about all the services" << endl;
		cout << TAB << "2- Show a day services" << endl;
		cout << TAB << "3- Show services between two dates" << endl;
		cout << TAB << "4- Show services about one customer" << endl;
		cout << TAB << "5- Insert new service" << endl;
		cout << TAB << "0- Back" << endl << endl;
		cout << "What is the option that you want? ";
		cin >> chosenOption;

		cleanDisplay();
		switch (chosenOption)
		{
		case '1':
			showAllServicesInfo(central.getServices());
			break;

		case '2':
			showServicesDay(central.getServices());
			break;

		case '3':
			showServicesBetweenDays(central.getServices());
			break;

		case '4':
			oneCustomerServicesMenu(central);
			break;

		case '5':
			central.insertNewService();
			break;

		case '0':
		{
			cleanDisplay();
			return 0;
		}

		default:
			cout << "Invalid option. Try again." << endl;
			break;
		}

	} while (chosenOption != '0');

	return 1;
}


/******************************************
				Routes Menu
 ******************************************/

/**
 * Shows the routes menu
 * @param central Central taxis
 */
unsigned short int routesMenu(CentralTaxis &central)
{
	char chosenOption;
	cleanDisplay();

	do
	{
		cout << endl << endl;
		cout << TAB_BIG << "ROUTES MENU" << endl;
		cout << endl;
		cout << TAB << "1- Show available routes" << endl;
		cout << TAB << "2- Remove a route" << endl ;
		cout << TAB << "3- Insert new route" << endl;
		cout << TAB << "0- Back" << endl << endl;

		cout << TAB << "What is the option that you want? ";
		cin >> chosenOption;

		cleanDisplay();
		switch (chosenOption)
		{
		case '1':
			showAvailableRoutes(central.getRoutes());
			break;

		case '2':
			central.removeRoute();
			break;

		case '3':
			central.insertNewRoute();
			break;

		case '0':
		{
			cleanDisplay();
			return 0;
		}

		default:
			cout << "Invalid option. Try again." << endl;
			break;
		}

	} while (chosenOption != '0');

	return 1;
}

/******************************************
				Main Menu
 ******************************************/
/**
 * Shows the Central Taxi logo
 */
void showLogo()
{
	cout << ".-----.            _    .--.              .-.             .-.  " << endl;
	cout << "`-. .-'           :_;  : .--'            .' `.            : :  " << endl;
	cout << "  : : .--.  .-.,-..-.  : :    .--. ,-.,-.`. .'.--.  .--.  : :  " << endl;
	cout << "  : :' .; ; `.  .': :  : :__ ' '_.': ,. : : : : ..'' .; ; : :_ " << endl;
	cout << "  :_;`.__,_;:_,._;:_;  `.__.'`.__.':_;:_; :_; :_;  `.__,_;`.__;" << endl;
}

/**
 * Shows the main menu
 * @param central Central taxis
 */
unsigned short int mainMenu(CentralTaxis &central)
{
	cleanDisplay();
	cout << endl << "Welcome!" << endl << endl;
	showLogo();

	char chosenOption;

	do
	{
		cout << endl << endl;
		cout << TAB_BIG << "Main Menu" << endl;
		cout << endl;
		cout << TAB << "1- Customers management" << endl;
		cout << TAB << "2- Services management" << endl;
		cout << TAB << "3- Routes management" << endl;
		cout << TAB << "4- Show discounts availables" << endl;
		cout << TAB << "0- Exit program" << endl << endl;

		cout << TAB << "What is the option that you want? ";
		cin >> chosenOption;
		cout << endl;

		switch (chosenOption)
		{
		case '1':
			customersMenu(central);
			break;

		case '2':
			servicesMenu(central);
			break;

		case '3':
			routesMenu(central);
			break;
		case '4':
			central.showDiscounts();
			break;
		case '0':
			return 0;

		default:
			cout << "Invalid option. Try again." << endl;
			break;
		}

	} while (chosenOption != '0');

	return 1;

}
