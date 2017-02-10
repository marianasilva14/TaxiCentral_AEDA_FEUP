/*
 * Customer.h
 *
 */

#pragma once

#include "Service.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <utility>

using namespace std;
class Service;

class Customer
{
private:
	string name;
	string address;
	unsigned int nif;
	int phoneNumber;

public:
	Customer(unsigned int nif, string name, string address, int phoneNumber);
	virtual ~Customer();

	enum CUSTOMER_TYPE
	{
		CompanyCustomer,
		PrivateCustomer
	};

	string getName();
	string getAddress();
	int getPhoneNumber();
	float getPoints();
	unsigned int getNif() const;
	void setName(string);
	void setAddress(string);
	void setPhoneNumber(int);
	virtual float getDiscount() = 0;
	virtual void accumulateService(Service*) = 0;
	virtual CUSTOMER_TYPE getCustomerType() = 0;
	virtual string getInformation();
	virtual string toFileFormat();
};

class InvalidNifException
{
public:
	friend ostream & operator<<(std::ostream &out, InvalidNifException &e)
	{
		out << "Error: Nif not valid!" << endl << endl;

		return out;
	}
};

class InvalidPhoneNumberException
{
public:
	friend ostream & operator<<(std::ostream &out, InvalidPhoneNumberException &e)
	{
		out << "Error: Phone number not valid!" << endl << endl;

		return out;
	}
};

unsigned int readCustomerNif();

Customer* customerExists(unsigned int, vector<Customer*>);

unsigned int readCustomerPhoneNumber();

Customer* customerExists(unsigned int, vector<Customer*>);

bool verifyNifAlreadyExist(unsigned int, vector<Customer*>);

bool compareByNif( Customer*, Customer*);

void showAllCustomersInfo(vector<Customer*>);

void showCustomersInfoByNif(vector<Customer*>);

void showCustomersInfoByName(vector<Customer*>);

void showAllCustomersInfoByType(vector<Customer*> customers, char type);
