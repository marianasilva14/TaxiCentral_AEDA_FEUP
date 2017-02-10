#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <ctime>

#include "Date.h"

using namespace std;

/**
 * Empty constructor.
 */
Date::Date()
{

}

/**
 * The constructor of the Date class, where the elements are initialized.
 * @param day day of the date
 * @param moth month of the date
 * @param year year of the date
 */
Date::Date(unsigned int day, unsigned int month, unsigned int year)
{
	setYear(year);
	setMonth(month);
	setDay(day);
}

/**
 * The constructor of the Date class, where the elements are initialized.
 * This constructor receive the date as a string.
 * @param dayMonthYear the date string
 */
Date::Date(string dayMonthYear)
{
	setDate(dayMonthYear);
	// sscanf(dayMonthYear.c_str(), "%d/%d/%d", &day, &month, &year);
}

/**
 * Set the year of the date
 * @param year year of the date
 */
void Date::setYear(unsigned int year)
{
	this->year = year;
}

/**
 * Set the month of the date
 * @param month of the date
 */
void Date::setMonth(unsigned int month)
{
	this->month = month;
}

/**
 * Set the day of the date
 * @param day of the date
 */
void Date::setDay(unsigned int day)
{
	this->day = day;
}

/**
 * Set the date
 * If day, month or year are not valid, make whole date invalid.
 * @param date date
 */
void Date::setDate(string date)
{
	if(sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) != 3)
	{
		/* if day, month or year are not valid, make whole date invalid */
		setDay(0);
		setMonth(0);
		setYear(0);
	}
}

/**
 * Year is a private unsigned integer of the Date class, we use "get" to be able to access this element in other classes.
 */
unsigned int Date::getYear() const
{
	return year;
}

/**
 * Month is a private unsigned integer of the Date class, we use "get" to be able to access this element in other classes.
 */
unsigned int Date::getMonth() const
{
	return month;
}

/**
 * Day is a private unsigned integer of the Date class, we use "get" to be able to access this element in other classes.
 */
unsigned int Date::getDay() const
{
	return day;
}

/**
 * This function convert a string(who is a date) to the following format: day/moth/year.
 * @return a string with the date in the format needed
 */
string Date::dateAsString()
{
	stringstream ss;
	ss << to_string(day) << "/" << to_string(month) << "/" << to_string(year);
	return ss.str();
}

/**
 * This function shows a date with the following format: day/moth/year.
 */
void Date::show()
{
	cout << day << "/" << month << "/" << year << endl;
}

/**
 * This function checks if the year is leap.
 * @return if the year is leap
 */
bool Date::isLeapYear()
{

	if(year % 2 == 0 && year % 100 != 0)
		return true;
	else if(year % 400 == 0)
		return true;
	else
		return false;
}

/**
 * This function verify if the day is valid, according to the month days.
 * @return the number of days in a month
 */
unsigned int Date::nDays()
{
	if(month == 4 || month == 6 || month == 9 || month == 11)
		return 30;
	else if (month == 2)
	{
		if(isLeapYear())
			return 29;
		else
			return 28;
	}
	else
		return 31;
}

/**
 * This function verify is a date is valid.
 * @return if the date is valid
 */

bool Date::isValid()
{
	if(day <= nDays() && (month > 0 && month < 13))
		return true;
	else
		return false;
}

/**
 * Check if dates are equal.
 * @param date the second date to compare
 * @return if two dates are equal
 */
bool Date::operator==(const Date &date)
{
	return year == date.getYear() && month == date.getMonth() && day == date.getDay();
}

/**
 * Check if one date is equal to or greater than another.
 * @param date the second date to compare
 * @return if one date is equal to or greater than another
 */
bool Date::operator>=(const Date &date)
{
	int date1 = year * 10000 + month * 100 + day;
	int date2 = date.getYear() * 10000 + date.getMonth() * 100 + date.getDay();

	return (date1 >= date2);
}

/**
 * Check if one date is equal to or less than another.
 * @param date the second date to compare
 * @return if one date is equal to or less than another
 */
bool Date::operator<=(const Date &date)
{
	int date1 = year * 10000 + month * 100 + day;
	int date2 = date.getYear() * 10000 + date.getMonth() * 100 + date.getDay();

	return (date1 <= date2);
}

/**
 * Get the next month of a date and update the date.
 * @return the new date
 */
Date Date::getNextMonth()
{
	Date date(realTime());
	//Date date("30/01/2016");

	date.month = date.month+1;

	while(!date.isValid())
	{

		if(date.month == 13)
		{
			date.year = year+1;
			date.month = 1;
		}
		else
		{
			int difference;
			if(date.month == 2)
			{
				if(date.isLeapYear())
					difference = date.day-29;
				else
					difference = date.day-28;

				date.month = 3;

			}
			else
			{
				if(date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11)
					difference = date.day-30;
				else
					difference = date.day-31;
			}

			date.day = difference;
		}
	}

	return date;
}


/**
 * Function that returns the system date.
 * @return a string with the system date
 */
string realTime()
{
	time_t t = time(0); // time now

	struct tm * now = localtime(& t);

	int day = now->tm_mday;
	int month = now->tm_mon;
	int year = now->tm_year + 1900;

	Date newDate(day, month + 1, year);

	return newDate.dateAsString();
}
