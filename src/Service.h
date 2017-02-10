/*
 * Service.h
 *
 */

#pragma once

#include "Route.h"
#include "Date.h"
#include "Customer.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "utilities.h"


using namespace std;

class Customer;

enum PAYMENT_TYPE
{
	Cash,
	ATM,
	Credit,
	EndOfMonth
};

class Service
{
private:
	Customer* customer;
	double cost;
	Route* route;
	Date date;
	int time;
	PAYMENT_TYPE payment;

public:
	static double rateForKm;
	static double rateForExtraMin;
	Service(Customer* customer, double cost, Route* route, Date date, int time, string payment);
	~Service();

	Customer* getCustomer();
	double getCost();
	Route* getRoute();
	Date getDate();
	int getTime();
	string getTimeinFormat();
	PAYMENT_TYPE getPayment();
	string getInformation();
	string getPaymentAsString();
	string toFileFormat();
};


void showServices(vector<Service*> services);

void showAllServicesInfo(vector<Service*> services);

void printServicesTable();

void showServicesDay(vector<Service*> services);

void showServicesBetweenDays(vector<Service*> services);

void showCustomerServicesByNif(vector<Service*> services, vector<Customer*> customers);

void showCustomerServicesByName(vector<Service*> services, vector<Customer*> customers);

