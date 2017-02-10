#include "Route.h"


/**
 * The constructor of the Route class, where the elements are initialized.
 * @param source service source
 * @param arrival service arrival
 * @param distance route distance
 * @param expectedTime route expected time
 */
Route::Route(string source, string arrival, double distance, int expectedTime)
{
	this->source = source;
	this->arrival = arrival;
	this->distance = distance;
	this->expectedTime = expectedTime;
}

/**
 * The constructor of the Route class, where the elements are initialized.
 * @param source service source
 * @param arrival service arrival
 */
Route::Route(string source, string arrival)
{
	this->source = source;
	this->arrival = arrival;
}

/**
 * The destructor
 */
Route::~Route() {}

/**
 * Source is a private string of the Route class, we use "get" to be able to access this element in other classes.
 * @return route source
 */
string Route::getSource()
{
	return source;
}

/**
 * Arrival is a private string of the Route class, we use "get" to be able to access this element in other classes.
 * @return route arrival
 */
string Route::getArrival()
{
	return arrival;
}

/**
 * Distance is a private double of the Route class, we use "get" to be able to access this element in other classes.
 * @return route distance
 */
double Route::getDistance()
{
	return distance;
}

/**
 * ExpectedTime is a private integer of the Route class, we use "get" to be able to access this element in other classes.
 * @return route expected time
 */
int Route::getExpectedTime()
{
	return expectedTime;
}

/**
 * Function that returns a string with the expected time of a route with the following format: "15h30m".
 * @return a string with the expected time in the formated needed
 */
string Route::getExpectedTimeinFormat()
{
	int hour = expectedTime / 60;
	int minutes = expectedTime %60;

	stringstream tmp;
	tmp << hour << 'h' << minutes << 'm';

	return tmp.str();
}

/**
 * Set the route source
 * @param new route source
 */
void Route::setSource(string source)
{
	this->source = source;
}

/**
 * Set the route arrival
 * @param new route arrival
 */
void Route::setArrival(string arrival)
{
	this->arrival = arrival;
}

/**
 * Set the route distance
 * @param new route distance
 */
void Route::setDistance(double distance)
{
	this->distance=distance;
}

/**
 * Set the route expected time
 * @param new route expected time
 */
void Route::setExpectedTime(int expectedTime)
{
	this->expectedTime = expectedTime;
}

/**
 * Get a route information in line with the routes table.
 * @return a string with the route information
 */
string Route::getInformation()
{

	stringstream information;
	information << setw(20) << this->getSource();
	information << setw(20) << this->getArrival();
	information << setw(17) << this->getDistance();
	information << setw(17) << this->getExpectedTimeinFormat();
	return information.str();
}

/**
 * Returns a string with all information of the route in the format needed.
 * @return a string with the route information in the format needed
 */
string Route::toFileFormat()
{
	stringstream information;

	information << this->getSource() << ";" <<this->getArrival() << ";"
			<< this->getDistance() << ";" << this->getExpectedTime();

	return information.str();
}

/**
 *
 * General functions for routes
 *
 *
 * */


/**
 * Ask the user for the route distance and checks if its's a number.
 * @return route distance
 * @throw InvalidDistanceExpection
 */
double readDistance()
{
	string input;
	double distance;

	cout << "Distance of this route: ";
	cin >> input ;

	if(is_number(input))
	{
		std::stringstream convertor(input);
		convertor >> distance;
		return distance;
	}
	else
		throw InvalidDistanceException();

}

/**
 * Ask the user for the route expected time and checks if its's a number.
 * @return expected time
 * @throw InvalidExpectedTimeException
 */
int readExpectedTime()
{

	string input;
	double expectedTime;

	cout << "Expected time of this route (minutes): ";
	cin >> input ;

	if(is_number(input))
	{
		std::stringstream convertor(input);
		convertor >> expectedTime;
		return expectedTime;
	}
	else
		throw InvalidExpectedTimeException();

}

/**
 * Show all the routes information in line with the routes table.
 * @param routes available routes
 */
void showAvailableRoutes(vector<Route*> routes)
{
	printRoutesTable();

	for(size_t i = 0; i < routes.size(); i++)
		cout << routes[i]->getInformation() << endl;

	cout << endl << endl;
}

/**
 * Print the routes table
 */
void printRoutesTable()
{
	cout << endl << setw(20)<< "Source" << setw(20) << "Arrival" << setw(17) << "Distance"<< setw(17) << "Expected Time" << endl;
	cout << " ----------------------------------------------------------------------------- " << endl;
}


