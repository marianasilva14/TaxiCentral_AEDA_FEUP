#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>

#include "Date.h"

using namespace std;

class Voucher
{
private:
	Date duration;
	double value;

public:
	Voucher(Date duration, double value);
	void setValue(double);
	void setDate(Date);
	Date getDuration();
	double getValue();
	string getInformation();
	string toFileFormat();
};
