#include "Customer.h"

/******************************************************/
/*             CUSTOMER CLASS FUNCTIONS               */
/******************************************************/

/**
 * The constructor of the Customer class, where the elements are initialized.
 * @param nif customer nif
 * @param name customer name
 * @param address customer address
 * @param phoneNumber customer phone number
 */
Customer::Customer(unsigned int nif, string name, string address, int phoneNumber)
{
	this->nif = nif;
	this->name = name;
	this->address = address;
	this->phoneNumber = phoneNumber;
}

/**
 * The destructor.
 */
Customer::~Customer()
{

}

/**
 * Name is a private string of the Customer class, we use "get" to be able to access this element in other classes.
 * @return customer name
 */
string Customer::getName()
{
	return name;
}

/**
 * Address is a private string of the Customer class, we use "get" to be able to access this element in other classes.
 * @return customer address
 */
string Customer::getAddress()
{
	return address;
}

/**
 * PhoneNumber is a private integer of the Customer class, we use "get" to be able to access this element in other classes.
 * @return customer phone number
*/
int Customer::getPhoneNumber()
{

	return phoneNumber;
}

/**
 * Nif is a private unsigned integer of the Customer class, we use "get" to be able to access this element in other classes.
 * @return customer nif
 */
unsigned int Customer::getNif() const
{
	return nif;
}

/**
 * Set the customer name.
 * @param customer name
 */
void Customer::setName(string name)
{
	this->name= name;
}

/**
 * Set the customer address.
 * @param customer address
 */
void Customer::setAddress(string address)
{
	this->address= address;
}

/**
 * Set the customer phone number.
 * @param customer phone number
 */
void Customer::setPhoneNumber(int phoneNumber)
{
	this->phoneNumber=phoneNumber;
}






/******************************************************/
/*           CUSTOMERS GENERAL FUNCTIONS              */
/******************************************************/


/*
   Validates all id inputs customers
 */
/**
 * Read the customer NIF.
 * @return customer nif
 * @throw InvalidNifException
 */
unsigned int readCustomerNif()
{
	string input;
	unsigned int nif;

	cout << "NIF customer: ";
	cin >> input ;
	cout << endl;

	std::stringstream convertor(input);

	if(is_number(input) && input.size() == 9)
	{
		std::stringstream convertor(input);
		convertor >> nif;
		return nif;
	}
	else
		throw InvalidNifException();

}

/**
 * Read the customer phone number.
 * @return customer phone number
 * @throw InvalidPhoneNumberException
 */
unsigned int readCustomerPhoneNumber()
{
	string input;
	unsigned int phone;

	cout << "Phone number: ";
	cin >> input ;

	std::stringstream convertor(input);

	if(is_number(input))
	{
		std::stringstream convertor(input);
		convertor >> phone;
		return phone;
	}
	else
		throw InvalidPhoneNumberException();

}

/**
 * Function used while sorting customers by name.
 * @param name_a first customer to compare
 * @param name_b second customer to compare
 * @return if the name_a is less than name_b
 */
bool compareByName( Customer* name_a,Customer* name_b)
{
	return name_a->getName() < name_b->getName();
}

/**
 * Function used while sorting customers by nif.
 * @param nif_a first customer to compare
 * @param nif_b second customer to compare
 * @return if the nif_a is less than nif_b
 */
bool compareByNif( Customer* nif_a, Customer* nif_b)
{
	return nif_a->getNif() < nif_b->getNif();
}

/**
 * Print the customer table.
 */
void printCustomerTable()
{
	cout << setw(3) << "TYPE" << setw(14) << "NIF" << setw(25) << "Name" << setw(54) << "Address"
			<< setw(20) << "Phone" << setw(20) << "Points/Cost" << endl;
	cout << " ----------------------------------------------------------------"
			"-------------------------------------------------------------------------- " << endl;
}

/**
 * Print the customer table type.
 * @param type customer type
 */
void printCustomerTableType(char type)
{
	if(type == 'P')
		cout << setw(14) << "NIF" << setw(25) << "Name" << setw(54) << "Address" << setw(20) << "Phone" << setw(20) << "Points" << endl;
	else
		cout << setw(14) << "NIF" << setw(25) << "Name" << setw(54) << "Address" << setw(20) << "Phone" << setw(20) << "Cost" << endl;

	cout << " ----------------------------------------------------------------"
			"-----------------------------------------------------------------" << endl;
}


/**
 * Show all the customer information in line with the customer table.
 * @param customers vector of customers
 */
void showAllCustomersInfo(vector<Customer*> customers)
{

	std::sort(customers.begin(), customers.end(), compareByName);

	cout << endl << endl;
	if(customers.size() != 0)
	{
		printCustomerTable();
		for(size_t i = 0; i < customers.size() ; i++)
			cout << customers[i]->getInformation();
	}
	else
		cout << "Customers not found!" ;
	cout << endl << endl;
}

/**
 * Show all the customer information by customer type in line with the customer table.
 * @param customers vector of customers
 * @param type customer type
 */
void showAllCustomersInfoByType(vector<Customer*> customers, char type)
{
	if(customers.size() != 0)
	{
		printCustomerTableType(type);
		if(type == 'P')
		{
			for(size_t i = 0; i < customers.size() ; i++)
				if(customers[i]->getCustomerType() == Customer::PrivateCustomer)
					cout << customers[i]->getInformation();
		}
		else
		{
			for(size_t i = 0; i < customers.size() ; i++)
				if(customers[i]->getCustomerType() == Customer::CompanyCustomer)
					cout << customers[i]->getInformation();
		}
	}
	else
		cout << "Customers not found!" ;
	cout << endl << endl;
}

/**
 * Get a customer information in line with the customer table.
 * @return a string with the customer information
 */
string Customer::getInformation()
{
	stringstream information;
	information << setw(15) << this->getNif();
	information << setw(25) << this->getName();
	information << setw(55) << this->getAddress();
	information << setw(20) << this->getPhoneNumber();
	return information.str();
}


/**
 * Returns a string with all information of the customer in the format needed.
 * @return a string with the customer information in the format needed
 */
string Customer::toFileFormat()
{
	stringstream information;
	information << this->getNif() << ";" <<this->getName() << ";"
			<< this->getAddress() << ";" << this->getPhoneNumber();

	return information.str();
}

/**
 * Verify if the customer exists, if not return a null customer.
 * @param nif customer nif to look for
 * @param customers customers vector
 * @return the customer with the nif receive
 */
Customer* customerExists(unsigned int nif, vector<Customer*> customers)
{

	for(size_t i= 0 ; i < customers.size(); i++)
		if(customers[i]->getNif() == nif)
			return customers[i];

	return NULL;
}

/**
 * Verify if the customer nif already exists
 */
bool verifyNifAlreadyExist(unsigned int nif, vector<Customer*> customers)
{
	int a = 0;
	int b = customers.size()-1;
	int c = (a+b)/2;

	bool found = false;

	while(a < b && !found)
	{
		if(customers[c]->getNif() == nif)
			found = true;
		else if(customers[c]->getNif() > nif)
			b = c-1;
		else
			a = c+1;

		c = (a+b)/2;
	}

	return found;
}

/**
 * Shows the information of one customer, who is searched by the NIF.
 * @param customers customers vector
 */
void showCustomersInfoByNif(vector<Customer*> customers)
{
	try {
		cout << endl << endl;
		unsigned int nif = readCustomerNif();
		Customer* customer = customerExists(nif, customers);

		if(customer !=  NULL)
		{
			printCustomerTable();
			cout << customer->getInformation() << endl;
		}
		else
			cout << "Customer not found!" << endl << endl;
	}
	catch(InvalidNifException &e)
	{
		cout << e;
	}
}

/**
 * Shows the information of one customer, who is searched by the name.
 * @param customers customers vector
 */
void showCustomersInfoByName(vector<Customer*> customers)
{
	cout << endl << endl;
	string name;
	cout << "Name: " ;
	cin.ignore();
	getline(cin, name);
	cout << endl << endl;
	std::transform(name.begin(), name.end(), name.begin(), ::tolower);

	bool found = false;
	size_t i = 0;
	while(!found && i < customers.size())
	{

		string nameCustomer = customers[i]->getName();
		std::transform(nameCustomer.begin(), nameCustomer.end(), nameCustomer.begin(), ::tolower);

		if(nameCustomer == name)
			found = true;
		else
			i++;
	}

	if(found)
	{
		printCustomerTable();
		cout << customers[i]->getInformation() << endl;
	}
	else
		cout << "Customer not found!" << endl;
}
