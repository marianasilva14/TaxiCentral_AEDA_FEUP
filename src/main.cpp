#include "Menu.h"
#include "CentralTaxis.h"

#include<iostream>
#include<iomanip>

using namespace std;

int main()
{
	string nameCentralTaxis = "Taxis XPTO";
  
  string vouchersFile = "../db/vouchers.txt";
  string customersFile = "../db/customers.txt";
  string servicesFile = "../db/services.txt";
  string routesFile = "../db/routes.txt";

	map<int, Voucher*> mapVouchers;

	CentralTaxis central(nameCentralTaxis, vouchersFile, customersFile, servicesFile, routesFile);
	bool vouchersSuccess = central.readVouchersFile(mapVouchers);
	bool customersSuccess = central.readCustomersFile(mapVouchers);
	bool servicesSuccess = central.readServicesFile();
	bool routesSuccess = central.readRoutesFile();
	central.loadVouchers(mapVouchers);

	if(!(vouchersSuccess && customersSuccess && servicesSuccess && routesSuccess))
    {
      cout << "Error while reading a file" << endl;
      return -1;
    }
	else
		mainMenu(central);

	return 0;
}
