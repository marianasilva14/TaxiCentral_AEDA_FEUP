#include "Voucher.h"

/**
 * The constructor of the Voucher class, where the elements are initialized.
 * @param value voucher deadline
 * @param value voucher value
 */
Voucher::Voucher(Date duration, double value)
{
	this->duration = duration;
	this-> value = value;
}

/**
 * Duration is a private date of the Voucher class, we use "get" to be able to access this element in other classes.
 * @return voucher deadline
 */
Date Voucher::getDuration()
{
	return duration;
}

/**
 * Value is a private double of the Voucher class, we use "get" to be able to access this element in other classes.
 * @return voucher value
 */
double Voucher::getValue()
{
	return value;
}

/**
 * Get a voucher information.
 * @return a string with the voucher information
 */
string Voucher::getInformation()
{
	stringstream information;
	information << this->getDuration().dateAsString() << setw(15) << (this->getValue()*100);
	return information.str();

}

/**
 * Set a voucher value.
 * @param voucher value
 */
void Voucher::setValue(double value)
{
	this->value = value;
}

/**
 * Set the deadline voucher
 * @param date voucher date
 */
void Voucher::setDate(Date date)
{
	this->duration = date;
}

/**
 * Returns a string with all information of the voucher in the format needed.
 * @return a string with the voucher information in the format needed
 */
string Voucher::toFileFormat()
{
	stringstream information;

	information << getDuration().dateAsString()<< ";" << getValue();

	return information.str();
}
