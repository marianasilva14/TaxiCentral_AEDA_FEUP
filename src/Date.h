/*
 * Date.h
 *
 */
#pragma once

#include <iostream>
#include <string>

using namespace std;

class Date
{
public:
  Date();
  Date(unsigned int day, unsigned int month, unsigned int year);
  Date(string dayMonthYear);
  void setYear(unsigned int year);
  void setMonth(unsigned int month);
  void setDay(unsigned int day);
  void setDate(string date);
  unsigned int getYear() const;
  unsigned int getMonth() const;
  unsigned int getDay() const;
  string dateAsString();
  void show();
  bool isValid();
  bool operator==(const Date &date);
  bool operator>=(const Date &date);
  bool operator<=(const Date &date);
  Date getNextMonth();

private:
  unsigned int year;
  unsigned int month;
  unsigned int day;
  bool isLeapYear();
  unsigned int nDays();
};

string realTime();
