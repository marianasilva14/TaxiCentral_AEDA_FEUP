#include "Service.h"

double Service::rateForKm = 1.0;
double Service::rateForExtraMin = 0.5;

/**
 * The constructor of the Service class, where the elements are initialized.
 * @param customer customer service
 * @param cost total value of the services performed by the customer
 * @param route service route
 * @param date service date
 * @param time duration of service
 * @param payment service type of payment
 */
Service::Service(Customer* customer, double cost, Route* route, Date date, int time, string payment)
{
	this->customer= customer;
	this->cost=cost;
	this->route=route;
	this->date= date;
	this->time=time;

	if(payment == "Cash")
		this->payment = PAYMENT_TYPE::Cash;
	else if(payment == "ATM")
		this->payment = PAYMENT_TYPE::ATM;
	else if(payment == "Credit")
		this->payment = PAYMENT_TYPE::Credit;
	else
		this->payment = PAYMENT_TYPE::EndOfMonth;
}

/**
 * The destructor
 */
Service::~Service(){}

/**
 * Customer is a private customer of the Service class, we use "get" to be able to access this element in other classes.
 * @return customer service
 */
Customer* Service::getCustomer()
{
	return customer;
}

/**
 * Cost is a private double of the Service class, we use "get" to be able to access this element in other classes.
 * @return total value of the services performed by the customer
 */
double Service::getCost()
{
	return cost;
}

/**
 * Route is a private route of the Service class, we use "get" to be able to access this element in other classes.
 * @return service route
 */
Route* Service::getRoute()
{
	return route;
}

/**
 * Date is a private date of the Service class, we use "get" to be able to access this element in other classes.
 * @return service date
 */
Date Service::getDate()
{
	return date;
}

/**
 * Time is a private integer of the Service class, we use "get" to be able to access this element in other classes.
 * @return service time
 */
int Service::getTime()
{
	return time;
}

/**
 * Get the time with the following format: "15h30m".
 * @return a string with the time in the format needed
 */
string Service::getTimeinFormat()
{
	int hour = time / 60;
	int minutes = time %60;

	stringstream tmp;
	tmp << hour << 'h' << minutes << 'm';

	return tmp.str();
}

/**
 * This "enumerator" type restricts existing payment types
 * @return payment type
 */
PAYMENT_TYPE Service::getPayment()
{
	return payment;
}

/**
 * Get the payment as a string
 * @return a string with the payment type
 */
string Service::getPaymentAsString()
{
	if(payment == 0)
		return "Cash";
	else if(payment == 1)
		return "ATM";
	else if(payment == 2)
		return "Credit";
	else
		return "EndOfMonth";
}

/**
 * Get a service information in line with the services table.
 * @return a string with the service information
 */
string Service::getInformation()
{
	stringstream information;


	if(this->getCustomer() == NULL)
		information << setw(12) << "N.R.  ";
	else
		information <<setw(12) << this->getCustomer()->getNif();


	information << setw(20) << this->getRoute()->getSource();
	information << setw(20) << this->getRoute()->getArrival();
	information << setw(17) << this->getDate().dateAsString();
	information << setw(10) << this->getTimeinFormat();
	information << setw(10) << this->getCost();
	information << setw(17) << this->getPaymentAsString();
	return information.str();
}

/**
 * Put a service information in the format needed.
 * @return a string with all information of the services in the format needed
 */
string Service::toFileFormat()
{
	stringstream information;

	//If casual customer
	if(customer == NULL)
		information << 000000000;
	else
		information << this->getCustomer()->getNif();

	information << ";" << this->getRoute()->getSource() << ";"
			<< this->getRoute()->getArrival() << ";" << this->getDate().dateAsString() << ";"
			<< this->getTime() << ";" << this->getCost() << ";" << this->getPaymentAsString();

	return information.str();
}

/**
 * Sort transactions by increasing date
 * @param s1 service one
 * @param s2 service two
 * @return if service one is more or equal than service two
 */
bool compareByDate( Service* s1, Service* s2)
{
	return !(s1->getDate() >= s2->getDate());
}

/**
 * Show all the services information in line with the services table.
 * @param services available services
 */
void showAllServicesInfo(vector<Service*> services)
{
	std::sort(services.begin(), services.end(), compareByDate);

	cout << endl << endl;
	printServicesTable();
	for(size_t i = 0; i < services.size() ; i++)
		cout << services[i]->getInformation() << endl;

	cout << endl << endl;
}

/**
 * Print the services table.
 */
void printServicesTable()
{
	cout << setw(12) << "NIF" << setw(20) << "Source" << setw(20) << "Arrival" << setw(17) << "Date";
	cout << setw(10) << "Time" << setw(10) << "Cost"  << setw(17)  << "Payment Type" <<  endl;
	cout << " --------------------------------------------------------------------------------------------------------- " << endl;
}

/**
 * Show the services of a day in line.
 * @services available services
 */
void showServicesDay(vector<Service*> services)
{
	cout << endl << endl;
	string date;
	bool service_found=false;
	bool date_valid=false;
	bool first_time=false;

	do {

		cout <<"Please enter the day(day/month/year): ";
		cin >> date;

		Date valid_date(date);

		if(!valid_date.isValid()){
			cout << "This date isn't valid." << endl;
		}
		else date_valid=true;

	} while(!date_valid);

	cout << endl << endl;

	for(size_t i=0; i < services.size();i++){

		if(services.at(i)->getDate() == date){
			if(!first_time){
				printServicesTable();
				service_found=true;
				cout << services.at(i)->getInformation() << endl;
				first_time=true;
			}
			else
				cout << services.at(i)->getInformation() << endl;

		}

	}

	if(!service_found)
		cout << "Services not found!" << endl;

}

/**
 * Show the services between two days in line.
 * @param services available services
 */
void showServicesBetweenDays(vector<Service*> services)
{
	cout << endl << endl;

	string date1,date2;
	bool service_found=false;
	bool date_valid=false;
	bool first_time=false;

	do {

		cout <<"Please enter the first day(day/month/year): ";
		cin >> date1;

		Date valid_date(date1);

		if(!valid_date.isValid()){
			cout << "This date isn't valid." << endl;
		}
		else date_valid=true;

	} while(!date_valid);


	date_valid=false;

	do {

		cout <<"Please enter the second day(day/month/year): ";
		cin >> date2;

		Date valid_date(date2);

		if(!valid_date.isValid()){
			cout << "This date isn't valid." << endl;
		}
		else date_valid=true;

	} while(!date_valid);

	cout << endl << endl;


	for(size_t i=0; i < services.size();i++)
	{

		if(services.at(i)->getDate()>= date1 && services.at(i)->getDate()<= date2)
		{
			if(!first_time){
				printServicesTable();
				service_found=true;
				cout << services.at(i)->getInformation() << endl;
				first_time=true;
			}
			else
				cout << services.at(i)->getInformation() << endl;

		}

	}

	if(!service_found)
		cout << "Services not found!" << endl;

}

/**
 * Show a customer service, searching by NIF.
 * @param services services available
 * @param customer Central taxis customers
 */
void showCustomerServicesByNif(vector<Service*> services, vector<Customer*> customers)
{
	try{
		cout << endl << endl;
		unsigned int nif = readCustomerNif();
		Customer* customer = customerExists(nif, customers);
		bool first_time=false;
		bool found = false;

		if(customer !=  NULL)
		{
			for(size_t i=0; i < services.size();i++){
				//unregistered customer
				if(services.at(i)->getCustomer() == NULL)
					continue;

				if(services.at(i)->getCustomer()->getNif() == nif)
				{

					if(!first_time){
						printServicesTable();
						first_time = true;
						found=true;
					}

					cout << services.at(i)->getInformation() << endl;
				}
			}

		}


		if(!found)
			cout << "Services not found!" << endl << endl;
	}
	catch(InvalidNifException &e)
	{
		cout << e;
	}

}

/**
 * Show a customer service, searching by name.
 * @param services services available
 * @param customer Central taxis customers
 */
void showCustomerServicesByName(vector<Service*> services, vector<Customer*> customers)
{
	cout << endl << endl;
	string name;
	cout << "Name: " ;
	cin.ignore();
	getline(cin, name);
	cout << endl << endl;

	nameToUpperCase(name);
	bool found = false;
	bool first_time=false;

	for(size_t i=0; i < services.size();i++){
		//unregistered customer
		if(services.at(i)->getCustomer() == NULL)
			continue;

		string nameCustomer = services.at(i)->getCustomer()->getName();

		if( nameCustomer == name){
			if(!first_time){
				printServicesTable();
				found=true;
				cout << services.at(i)->getInformation() << endl;
				first_time=true;
			}
			else
				cout << services.at(i)->getInformation() << endl;
		}


	}

	if(!found)
		cout << "Services not found!" << endl << endl;

}
