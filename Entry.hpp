#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Entry
{
    int key;
    string value;

public:
    Entry(string value); // pass value and let key be generated from random()
    Entry(int key, string value); //pass key and value manually
    void random(); //assign random number from 0 to 99 to key

    int getKey() const;

    string getValue() const;
	void setValue(string value);

    string toString() const;
};
