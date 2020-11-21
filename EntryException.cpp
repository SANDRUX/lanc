#include "EntryException.hpp"

EntryException::EntryException(string msg)
:msg(msg) //assign msg to msg
{
}

const char * EntryException::what() const throw()
{
	return msg.c_str(); //convert string to char* and return it
}
