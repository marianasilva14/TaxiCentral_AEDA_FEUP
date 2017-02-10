#pragma once

#include <locale>
#include <string>
#include<stdio.h>
#include<ctype.h>

#define ALTURA_ECRA 24

#define TAB_BIG "          "
#define TAB "   "

using namespace std;

inline void cleanDisplay()
{
	std::system("clear");
}

inline bool is_number(string &str)
{
	return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}

inline bool isAlphaOrSpace(string &str)
{
	size_t i = 0;
	while(i < str.size())
	{
		if(!(isalpha(str[i]) || isspace(str[i])))
		return false;

		i++;
	}
	return true;
}

inline void nameToUpperCase(string &phrase)
{
	for(size_t i = 0; i < phrase.size(); i++)
	{
		if(i ==  0)
			phrase[i]=toupper(phrase[i]);
		else if(phrase[i-1] == ' ')
			phrase[i]=toupper(phrase[i]);
		else
			phrase[i]=tolower(phrase[i]);
	}
}

