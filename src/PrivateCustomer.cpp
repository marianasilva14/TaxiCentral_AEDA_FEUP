#include "PrivateCustomer.h"

/**
 * The constructor of the private customer class, where the elements are initialized.
 * @param nif customer nif
 * @param name customer name
 * @param address customer address
 * @param phoneNumber customer phone number
 * @param points customer points
 */
PrivateCustomer::PrivateCustomer(unsigned int nif, string name, string address, int phoneNumber, int points) :
Customer(nif, name, address, phoneNumber)
{
	this->points = points;
}

/**
 * The destructor
 */
PrivateCustomer::~PrivateCustomer()
{

}

/**
 * Points is a private integer of the private customer class, we use "get" to be able to access this element in other classes.
 */
int PrivateCustomer::getPoints()
{
	return points;
}

/**
 * Function that through the points, get the discounts.
 * If the points are less than 50, the customer doesn't have discount.
 * If the points are more than 50 and less than 100, the discount is 0,1 percent.
 * If the points are more than 100 and less than 150, the discount is 0,2 percent.
 * If the points are more than 150 and less than 200, the discount is 0,3 percent.
 * If the points are more than 200 and less than 250, the discount is 0,4 percent.
 * If the points are more than 250, the discount is 0,5 percent.
 * @return the percent discount
 */
float PrivateCustomer::getDiscount()
{
	if(points < 50)
		return 0;
	else if(points >= 50 && points < 100)
		return 0.1;
	else if(points >= 100 && points < 150)
		return 0.2;
	else if(points >= 150 && points < 200)
		return 0.3;
	else if(points >= 200 && points < 250)
		return 0.4;
	else
		return 0.5;

}

/**
 * Function that accumulate the service points.
 * @param service Private customer service
 */
void PrivateCustomer::accumulateService(Service* service)
{
	int pointsService = (int)service->getCost()/10;
	this->points = this->points + pointsService;
	cout << "Points after this service: " << this->points << endl;
}

/**
 * This "enumerator" type restricts the types of existing customers
 * @return private customer
 */
Customer::CUSTOMER_TYPE PrivateCustomer::getCustomerType()
{
	return CUSTOMER_TYPE::PrivateCustomer;
}

/**
 * Get a private customer information in line.
 * @return a string with the customer information
 */
string PrivateCustomer::getInformation()
{

	stringstream information;

	information << setw(3) << "P";
	information << setw(15) << Customer::getInformation();
	information << setw(20) << this->points;
	information << endl;

	return information.str();
}

/**
 * Returns a string with all information of the customer in the format needed.
 * @return a string with the customer information in the format needed
 */
string PrivateCustomer::toFileFormat()
{
	stringstream information;

	information << "P" << ";" << Customer::toFileFormat() << ";" << this->points;

	return information.str();
}

/**
 * Reset the customer points
 */
void PrivateCustomer::resetPoints()
{
	this->points = 0;
}




