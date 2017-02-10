#pragma once

#include "Customer.h"
#include "Service.h"
#include "Voucher.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class CompanyCustomer: public Customer
{
private:
	double cost;
	Voucher* voucher;
public:
	CompanyCustomer(unsigned int nif, string name, string address, int phoneNumber, double cost);
	CompanyCustomer(unsigned int nif, string name, string address, int phoneNumber, double cost, Voucher* voucher);
	~CompanyCustomer();
	int getCost();
	float getDiscount();
	void resetCost();
	void accumulateService(Service* service);
	CUSTOMER_TYPE getCustomerType();
	string getInformation();
	string toFileFormat();
	Voucher* addVoucher(Voucher* voucher);
};

