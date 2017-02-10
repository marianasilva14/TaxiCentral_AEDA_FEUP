/*
 * CentralTaxis.h
 *
 */

#pragma once

#include "Customer.h"
#include "PrivateCustomer.h"
#include "CompanyCustomer.h"
#include "Service.h"
#include "Route.h"
#include "Voucher.h"
#include "Date.h"
#include "utilities.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <math.h>
#include <map>

class Service;

using namespace std;


class CentralTaxis
{
private:
	string name;
	string customersFile;
	string servicesFile;
	string routesFile;
	string vouchersFile;
	map<int,Voucher*> mapVouchers;
	vector<Customer*> customers;
	vector<Service*> services;
	vector<Route*> routes;

public:
	CentralTaxis(string name, string vouchersFile, string customersFile, string servicesFile, string routesFile);
	~CentralTaxis();
	void loadVouchers(map<int,Voucher*>&);

	vector<Customer*> getCustomers() const;
	vector<Service*> getServices() const;
	vector<Route*> getRoutes() const;

	string getCustomersFileName() const;
	string getServicesFileName() const;

	void editCustomerName();
	void editCustomerAddress();
	void editCustomerPhoneNumber();

	void removeCustomer();
	Customer* insertNewCustomer();
	void saveCustomers();

	void removeRoute();
	void insertNewRoute();
	Route* insertNewRoute(string, string);
	void saveRoutes();

	void insertNewService();
	Customer* processCustomerNewService();
	Route* findRoute(string, string);
	Route* processRouteNewService();
	int processTimeService();
	string processTypeOfPayment(Customer*);
	void processExtraRateService(double&, string);
	bool useDiscount(Customer*, float);
	bool offerVoucher(CompanyCustomer*);
	void saveServices();
	void saveVouchers();

	bool readFile(const string&, vector<string>&);
	bool readVouchersFile(map<int, Voucher*>&);
	bool readCustomersFile(const map<int, Voucher*> &);
	bool readServicesFile();
	bool readRoutesFile();

	void printVoucherTable();
	void showDiscounts();
};
