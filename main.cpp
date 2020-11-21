#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SkipList.hpp"

using namespace std;

void simulate()
{
	SkipList list; //creating the SkipList object

	int entryKeys[] = { 3, 19, 20, 124, 207, 301, 419, 1 }; //sample array of entry keys

	for (int key : entryKeys) list.put(key, "Entry number " + to_string(key)); //putting entries in the list

	list.print(cout);
	//cout << endl; //this will be needed if we decide to not put \n at the end inside list.print()

	list.erase(20); //testing the erase method
	list.print(cout);

	cout << "Looking for 207 gives us: " << list.find(207)->toString() << endl; //testing that find() works
	cout << "Looking for  20 gives us: " << list.find( 20)->toString() << endl; //testing that find() does not work on absent keys

	cout << "Looking for greater entry than 100 gives us: " << list.greaterEntry(100)->toString() << endl; //testing greaterEntry
	cout << "Looking for less entry than 300 gives us: " << list.lessEntry(100)->toString() << endl; //testing lessEntry

	SkipList list2; //create a new empty list

	for(int i = 0; i < 40; i++)
	{
		Entry* entry = new Entry("Entry number " + to_string(i)); //create entry with random key

		list2.put(entry->getKey(), entry->getValue()); //give entry's stats to list
	}

	list2.print(cout); //write out the list

	cout << endl << "All tests completed..." << endl;
}

int main()
{
	simulate();

	cout << "Did you like it? (y/n) ";
	char liked;
	cin >> liked;
}