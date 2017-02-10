#include "CompanyCustomer.h"

/**
 * The constructor of the CompanyCustomer class, where the elements are initialized.
 * As a new customer, at first the company don't have vouchers.
 * @param nif customer nif
 * @param name customer name
 * @param address customer address
 * @param phoneNumber customer phone number
 * @param cost total value of cutomer services
 */
CompanyCustomer::CompanyCustomer(unsigned int nif, string name, string address, int phoneNumber, double cost):
Customer(nif, name, address, phoneNumber)
{
	this->cost = cost;
	this->voucher = NULL;
}

/**
 * The constructor of the CompanyCustomer class, where the elements are initialized.
 * @param nif customer nif
 * @param name customer name
 * @param address customer address
 * @param phoneNumber customer phone number
 * @param cost total value of cutomer services
 * @param voucher company customer voucher
 */
CompanyCustomer::CompanyCustomer(unsigned int nif, string name, string address, int phoneNumber, double cost, Voucher* voucher):
Customer(nif, name, address, phoneNumber)
{
	this->cost = cost;
	this->voucher = voucher;
}

/**
 * The destructor
 */
CompanyCustomer::~CompanyCustomer()
{

}

/**
 * Cost is a private double of the CompanyCustomer class, we use "get" to be able to access this element in other classes.
 * @return total value of cutomer services
 */
int CompanyCustomer::getCost()
{
	return cost;
}

/**
 * If the date of the voucher is already available, return the value of the voucher.
 * @return value of company customer voucher
 */
float CompanyCustomer::getDiscount()
{
	if(voucher == NULL)
		return 0;

	Date dateOfDay(realTime());

	//verify if voucher is expired
	if(!(dateOfDay <= voucher->getDuration()))
		return 0;

	return voucher->getValue();
}

/**
 * Resets the company customer cost
 */
void CompanyCustomer::resetCost()
{
	this->cost = 0;
}

/**
 * This function adds to the cost the value of the service.
 * @param service available services
 */
void CompanyCustomer::accumulateService(Service* service)
{
	this->cost = cost + service->getCost();
}

/**
 * This "enumerator" type restricts the types of existing customers
 */
Customer::CUSTOMER_TYPE CompanyCustomer::getCustomerType()
{
	return CUSTOMER_TYPE::CompanyCustomer;
}

/**
 * Get the information of a customer in line.
 * @return string with the information of company customer service
 */
string CompanyCustomer::getInformation()
{
	stringstream information;

	information << setw(3) << "C";
	information << setw(15) << Customer::getInformation();
	information << setw(20) << this->cost;
	information << endl;

	return information.str();
}

/**
 * Put the information of a customer in the format needed.
 * @return string with all information of the customer in the format needed.
 */
string CompanyCustomer::toFileFormat()
{
	stringstream information;

	information << "C" << ";" << Customer::toFileFormat() <<  ";" << this->cost;

	return information.str();
}

/**
 * This function updates the deadline voucher.
 * Please note that if we want to add, for example, 30 days to the voucher, they must be 30 calendar days.
 * @param voucher CompanyCustomer voucher
 * @return the new voucher, this function can return the same voucher.
 */
Voucher* CompanyCustomer::addVoucher(Voucher* voucher)
{
	if(this->voucher == NULL)
	{
		this->voucher = voucher;
		return voucher;
	}
	else
	{
		double value = this->voucher->getValue() + voucher->getValue();

		//Date dateOfDay(realTime());
		Date dateOfDay("30/01/2016");
		Date nextMonth = dateOfDay.getNextMonth();
		this->voucher->setDate(nextMonth);

		if(value <= 0.20)
			this->voucher->setValue(value);
		else
			this->voucher->setValue(0.20);


	}

	return this->voucher;
}

