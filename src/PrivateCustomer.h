#pragma once

#include "Customer.h"
#include "Service.h"

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class PrivateCustomer : public Customer
{
private:
	int points;
public:
	PrivateCustomer(unsigned int nif, string name, string address, int phoneNumber, int points);
	~PrivateCustomer();
	int getPoints();
	float getDiscount();
	void accumulateService(Service* service);
	CUSTOMER_TYPE getCustomerType();
	string getInformation();
	string toFileFormat();
	void resetPoints();
};

