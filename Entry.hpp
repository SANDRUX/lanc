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
    Entry(string value);
    Entry(int key, string value);
    void random();
    int getKey() const;
    string getValue() const;
    string toString() const;
};
