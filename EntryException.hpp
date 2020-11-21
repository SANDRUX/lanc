#pragma once

#include <string>

using namespace std;

class EntryException final : public exception
{
	string msg; //message stored in exception

public:
	EntryException(string msg); //constructor that takes the message
	const char * what() const throw(); //the mainc function of an exception, telling us what went wrong
};