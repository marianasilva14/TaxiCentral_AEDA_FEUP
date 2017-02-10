#include "CentralTaxis.h"

/**
 * The constructor of the main class, where the elements are initialized.
 * @param name name of central taxi
 * @param vouchersFile file with customer vouchers
 * @param customerFile file with the information of the clients
 * @param servicesFile file with the information of the services
 * @param routesFile file with the information of the available routes
 */
CentralTaxis::CentralTaxis(string name, string vouchersFile, string customersFile, string servicesFile, string routesFile) :
mapVouchers(),
customers(),
services(),
routes()
{
	this->name = name;
	this->vouchersFile = vouchersFile;
	this->customersFile = customersFile;
	this->servicesFile = servicesFile;
	this->routesFile =routesFile;

}

CentralTaxis::~CentralTaxis()
{
	//cleanup customers
	for(size_t i = 0; i < customers.size(); i++)
		delete customers[i];

	//cleanup services
	for(size_t i = 0; i < services.size(); i++)
		delete services[i];

	//cleanup routes
	for(size_t i = 0; i < routes.size(); i++)
		delete routes[i];

	for (auto const& it : mapVouchers)
		delete it.second;
}

/**
 * Load vouchers from vouchers file in to mapVouchers
 * @param mapVouchers
 */
void CentralTaxis::loadVouchers(map<int,Voucher*> &mapVouchers)
{
	this->mapVouchers.insert(mapVouchers.begin(), mapVouchers.end());
}



/**
 * Customers is a private vector of the CentralTaxis class, we use "get" to be able to access this element in other classes.
 * @return customers vector
 */
vector<Customer*> CentralTaxis::getCustomers() const
{
	return customers;
}



/**
 * Services is a private vector of the CentralTaxis class, we use "get" to be able to access this element in other classes.
 * @return services vector
 */
vector<Service*> CentralTaxis::getServices() const
{
	return services;
}



/**
 * Routes is a private vector of the CentralTaxis class, we use "get" to be able to access this element in other classes.
 * @return routes vector
 */
vector<Route*> CentralTaxis::getRoutes() const
{
	return routes;
}



/**
 * CustomersFile is a private string of the CentralTaxis class, we use "get" to be able to access this element in other classes.
 * @return customers file
 */
string CentralTaxis::getCustomersFileName() const
{
	return customersFile;
}



/**
 * servicesFile is a private string of the CentralTaxis class, we use "get" to be able to access this element in other classes.
 * @return services vector
 */
string CentralTaxis::getServicesFileName() const
{
	return servicesFile;
}










/*
 *
 * Functions for Customers
 *
 *
 */


/**
 * This function edits a customer name.
 * The customer is searched by the NIF.
 * @throw InvalidNifException
 */
void CentralTaxis::editCustomerName()
{
	try{
		cout << endl << endl;
		unsigned int nif = readCustomerNif();

		Customer* customer = customerExists(nif, customers);

		if(customer ==  NULL)
			cout << "Customer not found! " << endl << endl;
		else
		{
			string newName;
			cout << "New name: ";
			getline(cin, newName);

			bool valid = false;
			while(!valid)
			{
				getline(cin, newName);
				cout << endl;

				if(isAlphaOrSpace(newName))
					valid = true;
				else
					cout << "Error! Name not valid! Try again: " ;
			}

			nameToUpperCase(newName);

			customer->setName(newName);
			saveCustomers();
			cout << endl << "Success, customer's name was modified. " << endl << endl;
		}
	}
	catch(InvalidNifException &e)
	{
		cout << e;
	}
}



/**
 * This function edits a customer address.
 * The customer is searched by the NIF.
 * @throw InvalidNifException
 */
void CentralTaxis::editCustomerAddress()
{
	try{
		cout << endl << endl;
		unsigned int nif = readCustomerNif();

		Customer* customer = customerExists(nif, customers);

		if(customer ==  NULL)
			cout << "Customer not found! " << endl << endl;
		else
		{
			string newAddress;
			cout << "New address: ";
			cin.ignore();
			getline(cin, newAddress);
			nameToUpperCase(newAddress);

			customer->setAddress(newAddress);
			saveCustomers();
			cout << endl << "Success, customer's address was modified. " << endl << endl;
		}
	}
	catch(InvalidNifException &e)
	{
		cout << e;
	}
}




/**
 * This function edits a customer phone number.
 * The customer is searched by the NIF.
 * @throw InvalidNifException
 */
void CentralTaxis::editCustomerPhoneNumber()
{
	try{
		cout << endl << endl;
		unsigned int nif = readCustomerNif();

		Customer* customer = customerExists(nif, customers);

		if(customer ==  NULL)
			cout << "Customer not found! " << endl << endl;
		else
		{
			int newPhone = readCustomerPhoneNumber();

			customer->setPhoneNumber(newPhone);
			saveCustomers();
			cout << endl << "Success, customer's phone number was modified. " << endl << endl;
		}

	}
	catch(InvalidNifException &e)
	{
		cout << e;
	}
	catch(InvalidPhoneNumberException &e)
	{
		cout << e;
	}
}



/**
 * This function removes a customer.
 * The customer is searched by the NIF.
 * @throws InvalidNifException
 */
void CentralTaxis::removeCustomer()
{
	try{
		cout << endl << endl;
		unsigned int nif = readCustomerNif();

		bool found = false;
		size_t i = 0;

		while (i < customers.size() && !found)
		{
			if(customers[i]->getNif() == nif)
			{
				found = true;
				delete customers[i];
				customers[i] = NULL;
				customers.erase(customers.begin()+i);
			}
			else i++;
		}

		if(found)
		{
			saveCustomers();
			cout << endl << "Success, customer's was removed. " << endl << endl;
		}
		else
			cout << "Customer not found! " << endl << endl;
	}
	catch(InvalidNifException &e)
	{
		cout << e;
	}
}



/**
 * This function inserts a new customer, ordered , in the vector.
 * @throw InvalidNifException
 * @throw InvalidPhoneNumberException
 */
Customer* CentralTaxis::insertNewCustomer()
{
	try{
		cleanDisplay();

		char typeCustomer;
		bool typeValid = false;

		cout << endl << endl;
		cout << TAB_BIG << "Select customer type:" << endl;
		cout << endl;
		cout << TAB << "1- Private customer" << endl;
		cout << TAB << "2- Company customer" << endl;

		while(!typeValid)
		{
			cout << "> " ;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> typeCustomer;

			if(typeCustomer == '1' || typeCustomer == '2')
				typeValid = true;
			else
			{
				cout << "Type of Customer wrong, try again : ";
				cout << endl;
			}
		}

		unsigned int nif = readCustomerNif();
		if(verifyNifAlreadyExist(nif, customers))
		{
			cout << "Error: Nif already exists." << endl;
			return customerExists(nif, customers);
		}

		string name;
		cout << "Name: ";

		bool valid = false;
		while(!valid)
		{
			cin.ignore();
			getline(cin, name);
			cout << endl;

			if(isAlphaOrSpace(name))
				valid = true;
			else
				cout << "Error! Name not valid! Try again: " ;
		}

		nameToUpperCase(name);

		string address;
		cout << "Address: ";
		getline(cin, address);

		unsigned int phoneNumber = readCustomerPhoneNumber();

		nameToUpperCase(name);
		nameToUpperCase(address);

		Customer* newCustomer;
		if(typeCustomer == '1')
			newCustomer = new PrivateCustomer(nif, name, address, phoneNumber, 0);
		else
			newCustomer = new CompanyCustomer(nif, name, address, phoneNumber, 0);

		size_t i = 0;
		bool finished = false;
		while(!finished)
		{
			if(i == customers.size()-1)
			{
				customers.push_back(newCustomer);
				finished = true;
			}

			else if(customers[i]->getNif() < newCustomer->getNif() && customers[i+1]->getNif() > newCustomer->getNif())
			{
				customers.insert( customers.begin() + i, newCustomer);
				finished = true;
			}

			i++;
		}

		saveCustomers();
		cout << endl << "Success, new customer's was added. " << endl << endl;
		return newCustomer;

	}
	catch(InvalidNifException &e)
	{
		cout << e;
		return NULL;
	}
	catch(InvalidPhoneNumberException &e)
	{
		cout << e;
		return NULL;
	}
}




/**
 * Save customers in file after modification
 */
void CentralTaxis::saveCustomers()
{
	ofstream c_file;
	c_file.open(customersFile);

	c_file << customers.size() << endl;

	for(size_t i = 0; i < customers.size() ; i++)
	{
		c_file << customers[i]->toFileFormat();

		if(i < customers.size()-1)
			c_file << endl;
	}

	c_file.close();
}










/*
 *
 * Functions for Routes
 *
 *
 */

/**
 * This function removes a route.
 * If the route exists it shows a message saying that it was successfully removed.
 * Otherwise it will show a message saying that the route wasn't found.
 */
void CentralTaxis::removeRoute()
{
	cout << endl << endl;
	string source;
	cout << "Source: ";

	bool valid = false;
	while(!valid)
	{
		cin.ignore();
		getline(cin, source);
		cout << endl;

		if(isAlphaOrSpace(source))
			valid = true;
		else
			cout << "Error! Source not valid! Try again: " ;
	}

	string arrival;
	cout << "Arrival: ";

	valid = false;
	while(!valid)
	{
		//cin.ignore();
		getline(cin, arrival);
		cout << endl;

		if(isAlphaOrSpace(arrival))
			valid = true;
		else
			cout << "Error! Arrival not valid! Try again: " ;
	}

	nameToUpperCase(source);
	nameToUpperCase(arrival);

	size_t i = 0;
	bool found = false;
	while(!found && i < routes.size())
	{
		string currArrival = routes[i]->getArrival();
		nameToUpperCase(currArrival);
		string currSource = routes[i]->getSource();
		nameToUpperCase(currSource);

		if(currArrival == arrival && currSource == source)
		{
			found = true;
			delete routes[i];
			routes[i] = NULL;
			routes.erase(routes.begin()+i);
		}
		i++;
	}

	if(found)
	{
		saveRoutes();
		cout << endl << "Success, routes's was removed. " << endl << endl;
	}
	else
		cout << "Route not found! " << endl << endl;
}



/**
 * This function inserts a new route.
 * @throw InvalidDistanceException
 * @throw InvalidExpectedTimeException
 */
void CentralTaxis::insertNewRoute()
{
	try{
		cout << endl << endl;
		string source;
		cout << "Source: ";

		bool valid = false;
		while(!valid)
		{
			cin.ignore();
			getline(cin, source);
			cout << endl;

			if(isAlphaOrSpace(source))
				valid = true;
			else
				cout << "Error! Source not valid! Try again: " ;
		}

		string arrival;
		cout << "Arrival: ";

		valid = false;
		while(!valid)
		{
			getline(cin, arrival);
			cout << endl;

			if(isAlphaOrSpace(arrival))
				valid = true;
			else
				cout << "Error! Arrival not valid! Try again: " ;
		}

		double distance = readDistance();

		int expectedTime = readExpectedTime();

		nameToUpperCase(source);
		nameToUpperCase(arrival);

		Route* newRoute = new Route(source,arrival,distance,expectedTime);
		routes.push_back(newRoute);
		saveRoutes();
		cout << endl << "Success, new route's was added. " << endl << endl;

	}
	catch(InvalidDistanceException &e)
	{
		cout << e;
	}
	catch(InvalidExpectedTimeException &e)
	{
		cout << e;
	}
}



/**
 * This function inserts a new route.
 * Receive a source and an arrival, and ask the user the distance and expected time.
 * @param source route source
 * @param arrival route arrival
 * @throw InvalidDistanceException
 * @throw InvalidExpectedTimeException
 *
 */
Route* CentralTaxis::insertNewRoute(string source, string arrival)
{
	try{

		double distance = readDistance();

		int expectedTime = readExpectedTime();

		Route* newRoute = new Route(source,arrival,distance,expectedTime);

		routes.push_back(newRoute);
		saveRoutes();
		cout << endl << "Success, new route's was added. " << endl << endl;
		return newRoute;

	}
	catch(InvalidDistanceException &e)
	{
		cout << e;
		return NULL;
	}
	catch(InvalidExpectedTimeException &e)
	{
		cout << e;
		return NULL;
	}
}



/**
 * Save routes in file after modification.
 */
void CentralTaxis::saveRoutes()
{
	ofstream c_file;
	c_file.open(routesFile);

	c_file << routes.size() << endl;

	for(size_t i = 0; i < routes.size() ; i++)
	{
		c_file << routes[i]->toFileFormat();

		if(i < routes.size()-1)
			c_file << endl;
	}

	c_file.close();
}










/*
 *
 * Functions for Services
 *
 *
 */

/**
 * This function processes a customer from a new service.
 * There are two options:
 * -If the customer is registered, the function search for the customer NIF and if it isn't valid throw an exception(InvalidNifException).
 * If the customer doesn't exist shows a message: "Nif not found, please try again.".
 * -For a casual customer the user can register him or proceed without registering".
 *  @throw InvalidNifException
 *  @return Customer that used the service
 *  @return NULL in case the customer is not registered
 */
Customer* CentralTaxis::processCustomerNewService()
{
	cleanDisplay();

	cout << endl << endl;
	cout << TAB_BIG << "Select customer type:" << endl;
	cout << endl;
	cout << TAB << "1- Registered customer" << endl;
	cout << TAB << "2- Not registered customer" << endl;

	char option;
	bool valid = false;
	while(!valid)
	{
		cout << "> " ;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> option;

		if(option == '1' || option == '2')
			valid = true;
		else
			cout << "Option not valid, try again";

	}

	if(option == '1')
	{
		Customer* customer = NULL;

		while(customer == NULL)
		{
			try{
				unsigned int nif = readCustomerNif();
				customer = customerExists(nif, customers);

				if(customer != NULL)
					return customer;
			}
			catch(InvalidNifException &e)
			{
				cout << e;
			}
			if(customer == NULL)
				cout << "Nif not found, please try again." << endl;
		}
	}
	else
	{
		cout << TAB << "1 - Insert new customer" << endl;
		cout << TAB << "2 - Proceed without registering" << endl;
		valid = false;
		while(!valid)
		{
			cout << "> " ;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> option;

			if(option == '1' || option == '2')
				valid = true;
			else
				cout << "Option not valid, try again";
		}

		if(option == '1')
		{
			Customer* customer = insertNewCustomer();
			return customer;
		}
	}

	return NULL;
}



/**
 * This function searches for a route.
 * @param source route
 * @param arrival route
 * @return Route or NULL if it doesn't exist
 */
Route* CentralTaxis::findRoute(string source, string arrival)
{
	size_t i = 0;
	while(i < routes.size())
	{
		string currArrival = routes[i]->getArrival();
		nameToUpperCase(currArrival);
		string currSource = routes[i]->getSource();
		nameToUpperCase(currSource);

		if( currArrival== arrival && currSource == source)
			return routes[i];
		i++;
	}

	return NULL;
}



/**
 * This function verifies if the route already exists.
 * If not, the user can insert a new route.
 * @return Route added
 */
Route* CentralTaxis::processRouteNewService()
{
	cleanDisplay();
	cout << endl << endl;
	string source;
	cout << "Source: ";

	bool valid = false;
	while(!valid)
	{
		cin.ignore();
		getline(cin, source);
		cout << endl;

		if(isAlphaOrSpace(source))
			valid = true;
		else
			cout << "Error! Source not valid! Try again: ";
	}

	string arrival;
	cout << "Arrival: ";

	valid = false;
	while(!valid)
	{
		getline(cin, arrival);
		cout << endl;

		if(isAlphaOrSpace(arrival))
			valid = true;
		else
			cout << "Error! Arrival not valid! Try again: ";
	}

	nameToUpperCase(source);
	nameToUpperCase(arrival);

	Route* route = findRoute(source, arrival);

	if(route == NULL)
	{
		cout << "Route not exist yet...";
		cout << endl << "Please insert new route:" << endl;
		route = insertNewRoute(source, arrival);
	}

	return route;
}



/**
 * This function asks the user for the service time and verify if it's valid.
 * @return time of the service
 */
int CentralTaxis::processTimeService()
{

	string input;
	double time = 0;

	cout << "Time of this service (minutes): ";

	bool valid = false;
	while(!valid)
	{
		cin >> input ;

		if(is_number(input))
		{
			std::stringstream convertor(input);
			convertor >> time;
			return time;
		}
		else
		{
			cout << endl << "Time not valid, try again: ";
			cin.ignore();
		}
	}

	return time;
}



/**
 * This function processes the type of payment.
 * If the customer is private, then the user can only pay with cash or ATM.
 * If the customer is private, then the user can only pay with all types of payment(cash,ATM,credit,end of the month).
 * @param customer CentralTaxis customer
 * @return payment_type
 */
string CentralTaxis::processTypeOfPayment(Customer* customer)
{
	cleanDisplay();

	char payment;

	cout << endl;
	cout << TAB_BIG << "Chose type of payment: " << endl;
	cout << TAB << "1- Cash" << endl;
	cout << TAB << "2- ATM" << endl ;
	bool valid = false;
	if(customer == NULL)
	{
		while(!valid)
		{
			cout << "> ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> payment;

			if(payment == '1' || payment == '2')
				valid = true;
			else
				cout << endl << "Payment type not valid, try again."<< endl;
		}
	}
	else
	{
		cout << TAB << "3- Credit" << endl;
		cout << TAB << "4- End of month" << endl ;
		while(!valid)
		{
			cout << "> ";
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> payment;

			if(payment == '1' || payment == '2' || payment == '3' || payment == '4')
				valid = true;
			else
				cout << endl << "Payment type not valid, try again."<< endl;

		}
	}

	switch (payment)
	{
	case '1':
		return "Cash";
		break;
	case '2':
		return "ATM";
		break;
	case '3':
		return "Credit";
		break;
	case '4':
		return "EndOfMonth";
		break;
	}

	return "Cash"; //security, in case
}



/**
 * This function processes the extra cost if the payment type is Credit or EndOfMonth
 * @param cost service cost
 * @param payment payment type
 */
void CentralTaxis::processExtraRateService(double &cost, string payment)
{
	double rate = 0;

	if(payment == "Credit")
	{
		rate = (ceil(0.02*cost*100))/100;
		cout << "Rate for Credit Payment = " << rate << endl;
	}

	else if(payment == "EndOfMonth")
	{
		rate = (ceil(0.05*cost*100))/100;
		cout << "Rate for End of month Payment = " << rate << endl;
	}

	cost += rate;
	cout << "Total cost: " << cost << endl;
}



/**
 * This function shows the customer discount available and asks the user if he wants to use it.
 * If the user answer "yes" the customer points are reseted.
 * @return if the discount is to be used
 */
bool CentralTaxis::useDiscount(Customer* customer, float discount)
{
	if(customer->getCustomerType() == Customer::CompanyCustomer)
		return true;


	cout << "You have a discount of : " << (100*discount) << " percentage." << endl << endl;
	cout << TAB << "Do you want to use it ?" << endl;
	cout << TAB << "1- Yes " << endl;
	cout << TAB << "2- No " << endl;

	char option;
	bool valid = false;
	while(!valid)
	{
		cout << "> " ;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin >> option;

		if(option == '1' || option == '2')
			valid = true;
		else
			cout << "Option not valid, try again";


	}

	if(option == '1')
	{
		PrivateCustomer* tmp = dynamic_cast<PrivateCustomer*>(customer);
		tmp->resetPoints();
		return true;
	}
	else
		return false;
}


/**
 * This function makes the company customers vouchers.
 * Adds a new voucher to customer object
 * @param customer company customer
 * @return if it was generate a new voucher
 */
bool CentralTaxis::offerVoucher(CompanyCustomer* customer)
{

	double value;
	if(customer->getCost() < 250)
		value = 0;
	else if(customer->getCost() >= 250 && customer->getCost() < 500)
		value = 0.05;
	else if(customer->getCost() >= 500 && customer->getCost() < 750)
		value = 0.10;
	else if(customer->getCost() >= 750 && customer->getCost() < 1000)
		value = 0.15;
	else
		value = 0.20;

	Voucher* voucher = NULL;
	if(value != 0)
	{
		Date dateOfDay(realTime());
		//Date dateOfDay("01/01/2016");

		Date nextMonth = dateOfDay.getNextMonth();
		voucher = new Voucher(nextMonth, value);
		voucher = customer->addVoucher(voucher);
		mapVouchers.insert( std::pair<int,Voucher*>(customer->getNif(),voucher));

		return true;
	}

	return false;
}




/**
 * This function inserts a new service.
 * The service value is calculated.
 * If the customer has available discounts, the service can use them if the customer wants.
 */
void CentralTaxis::insertNewService()
{
	Customer* customer = processCustomerNewService();
	Route* route = processRouteNewService();

	Date dateOfDay(realTime());
	//Date dateOfDay("30/01/2016");

	int time = processTimeService();
	string payment = processTypeOfPayment(customer);

	// computes cost and applies discount (if any)
	double cost = Service::rateForKm * route->getDistance() + (time - route->getExpectedTime()) * Service::rateForExtraMin;

	float discount = 0;
	if (customer != NULL)
	{
		discount = customer->getDiscount();
		if(discount != 0)
		{
			if(!useDiscount(customer, discount))
				discount = 0;

			else
			{
				cout << endl << "Cost of this service: " << cost << endl;
				cost -= cost*discount;
				cout << "Cost of this service with discount: " << cost << endl;
			}
		}
	}

	if(discount == 0)
		cout << endl << "Cost of this service: " << cost << endl;

	if(customer != NULL && (payment == "Credit" || payment == "EndOfMonth"))
		processExtraRateService(cost, payment);

	Service* newService = new Service(customer, cost, route, dateOfDay, time, payment);

	services.push_back(newService);
	saveServices();
	cout << endl << "Success, new Service was added. " << endl;


	//saves points or cost in customer if not null
	if(customer != NULL)
	{
		customer->accumulateService(newService);
		if(customer->getCustomerType() == Customer::CompanyCustomer)
			if (offerVoucher(dynamic_cast<CompanyCustomer*>(customer)))
			{
				CompanyCustomer* tmp = dynamic_cast<CompanyCustomer*>(customer);
				tmp->resetCost();
			}

		saveCustomers();
		saveVouchers();
	}

	cout << endl << endl;
}



/**
 * Save services in file after modification.
 */
void CentralTaxis::saveServices()
{
	ofstream c_file;
	c_file.open(servicesFile);

	c_file << services.size() << endl;

	for(size_t i = 0; i < services.size() ; i++)
	{
		c_file << services[i]->toFileFormat();

		if(i < services.size()-1)
			c_file << endl;
	}

	c_file.close();
}



/**
 * Save vouchers in file after modification.
 */
void CentralTaxis::saveVouchers()
{

	if(mapVouchers.size() != 0)
	{
		ofstream c_file;
		c_file.open(vouchersFile);

		c_file << mapVouchers.size() << endl;

		size_t i = 0;
		for (auto const& it : mapVouchers)
		{
			if(i == (mapVouchers.size()-1))
				c_file << it.first << ";" << it.second->toFileFormat();
			else
				c_file << it.first << ";" << it.second->toFileFormat() << endl;

			i++;
		}
		c_file.close();
	}
}


/*
 *
 * Functions for Discounts
 *
 *
 **/

/**
 * Print the voucher table.
 */
void CentralTaxis::printVoucherTable()
{
	cout << setw(12) << "NIF" << setw(20) << "Expires at" << setw(15) << " %" << endl;
	cout << " ---------------------------------------------------- " << endl;
}


/**
 * Print the available discounts.
 */
void CentralTaxis::showDiscounts()
{
	if(mapVouchers.size() != 0)
	{
		printVoucherTable();
		for (auto const& it : mapVouchers)
			std::cout << setw(12) << it.first << setw(35) << it.second->getInformation() << endl;
	}
	else
		cout << "No vouchers available" << endl;
}




/**
 *
 *  Functions to read files
 *
 *
 **/

/**
 * Reads a given file and separates it to a vector of its lines.
 * Returns true if success.
 * @param fileName file name
 * @param fileLines vector with file lines
 * @return if the file can be read
 */
bool CentralTaxis::readFile(const string &fileName, vector<string> &fileLines)
{
	ifstream cFile;
	string line;

	/* try to open the file */
	cFile.open(fileName.c_str());

	if(!cFile.is_open())
		return false;
	else
	{
		/* Read file content */
		while(getline(cFile, line))
			fileLines.push_back(line); /*store line in the vector*/
		cFile.close();
		return true;
	}
}




/**
 * Reads a vouchers file and save them in a mapVouchers.
 * @return if success.
 */
bool CentralTaxis::readVouchersFile(map<int, Voucher*> &mapVouchers)
{
	vector<string> vouchersLines;

	/* try to get the file lines */
	if(!readFile(vouchersFile, vouchersLines))
		return false;
	else
	{
		int nVouchers;
		stringstream ss(vouchersLines[0]);
		ss >> nVouchers;

		for(int i = 1; i <= nVouchers ; i++)
		{
			string substring;
			stringstream line(vouchersLines[i]);


			int nif;
			Date date;
			double value;

			int item = 0;
			string currItem;
			while(getline(line,currItem, ';'))
			{
				if(item == 0)
				{
					stringstream ss(currItem);
					ss >> nif;
				}
				else if(item == 1)
					date = currItem;
				else if(item == 2)
				{
					stringstream ss(currItem);
					ss >> value;
				}

				item++;
			}

			Voucher* newVoucher = new Voucher(date, value);
			mapVouchers.insert( std::pair<int,Voucher*>(nif,newVoucher));
		}
	}

	return true;
}



/**
 * Reads a customers file and save them in a customers vector.
 * @return if success.
 */
bool CentralTaxis::readCustomersFile(const map<int, Voucher*> &mapVouchers)
{
	vector<string> customersLines;

	/* try to get the file lines */
	if(!readFile(customersFile, customersLines))
		return false;
	else
	{
		int nCustomers;
		stringstream ss(customersLines[0]);
		ss >> nCustomers;

		for(int i = 1; i <= nCustomers ; i++)
		{
			string substring;
			stringstream line(customersLines[i]);

			string typeCustomer;
			unsigned int nif;
			string name;
			string address;
			int phoneNumber;
			int points;
			double cost;

			int item = 0;
			string currItem;
			while(getline(line,currItem, ';'))
			{
				if(item == 0)
					typeCustomer = currItem;
				else if(item == 1)
				{
					stringstream ss(currItem);
					ss >> nif;
				}
				else if(item == 2)
					name = currItem;
				else if(item == 3)
					address = currItem;
				else if(item == 4)
				{
					stringstream ss(currItem);
					ss >> phoneNumber;
				}
				else if(item == 5)
				{
					currItem = currItem.substr(0, currItem.size());
					stringstream ss(currItem);
					if(typeCustomer == "P")
						ss >> points;
					else
						ss >> cost;
				}

				item++;
			}


			Customer* newCustomer;
			if(typeCustomer == "P")
				newCustomer = new PrivateCustomer(nif, name, address, phoneNumber, points);
			else
			{
				Voucher* voucher = NULL;
				if(mapVouchers.find(nif) != mapVouchers.end())
					voucher = mapVouchers.find(nif)->second;
				newCustomer = new CompanyCustomer(nif, name, address, phoneNumber, cost, voucher);
			}
			customers.push_back(newCustomer);
		}
	}

	std::sort(customers.begin(), customers.end(), compareByNif);

	return true;
}



/*
 * Reads a service file and save them in a service vector.
 * @return if success.
 */
bool CentralTaxis::readServicesFile()
{
	vector<string> servicesLines;

	/* try to get the file lines */
	if(!readFile(servicesFile, servicesLines))
		return false;
	else
	{
		int nCustomers;
		stringstream ss(servicesLines[0]);
		ss >> nCustomers;

		for(int i = 1; i <= nCustomers ; i++)
		{
			string substring;
			stringstream line(servicesLines[i]);

			unsigned int nif;

			string origin;
			string destination;

			string startTime;
			string endTime;

			double cost;
			string paymentType;
			Date date;
			unsigned int time;
			int item = 0;
			string currItem;
			while(getline(line,currItem, ';'))
			{
				if(item == 0)
				{
					stringstream ss(currItem);
					ss >> nif;
				}
				else if(item == 1)
					origin = currItem;
				else if(item == 2)
					destination = currItem;
				else if(item == 3)
					date = currItem;
				else if(item == 4)
				{
					stringstream ss(currItem);
					ss >> time;
				}
				else if(item == 5)
				{
					stringstream ss(currItem);
					ss >> cost;
				}
				else if(item == 6)
					paymentType = currItem.substr(0, currItem.size());

				item++;
			}

			size_t j;
			for(j = 0; j < customers.size(); j++)
			{
				if(customers[j]->getNif() == nif)
					break;
			}

			Route* routeService = new Route(origin, destination);

			Service* newService = new Service(customers[j], cost, routeService, date, time, paymentType);

			services.push_back(newService);
		}
	}

	return true;
}




/*
 * Reads a routes file and save them in a routes vector.
 * @return if success.
 */
bool CentralTaxis::readRoutesFile()
{
	vector<string> routesLines;

	/* try to get the file lines */
	if(!readFile(routesFile, routesLines))
		return false;
	else
	{
		int nRoutes;
		stringstream ss(routesLines[0]);
		ss >> nRoutes;

		for(int i = 1; i <= nRoutes ; i++)
		{
			string substring;
			stringstream line(routesLines[i]);

			string source;
			string arrival;
			double distance;
			int expectedTime;

			int item = 0;
			string currItem;
			while(getline(line,currItem, ';'))
			{
				if(item == 0)
					source = currItem;
				else if(item == 1)
					arrival = currItem;
				else if(item == 2)
				{
					stringstream ss(currItem);
					ss >> distance;
				}
				else if(item == 3)
				{
					stringstream ss(currItem);
					ss >> expectedTime;
				}
				item++;
			}


			Route* newRoute = new Route(source, arrival, distance, expectedTime);
			routes.push_back(newRoute);
		}
	}

	return true;
}
