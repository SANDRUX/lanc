#pragma once

#include "Entry.hpp"
#include "QuadNode.hpp"

class SkipList
{
    const int layerCount = 25; //amount of layers the skip list will have

	//we have left and right end nodes as placeholders. They have maximum amount of layers and connect to each other

	QuadNode *bottomOfLeftSide; //bottom node of the left side
    QuadNode *topOfLeftGuy; //top node of the left side
	QuadNode *bottomOfEnd; //bottom node of the right end
    QuadNode *topOfEnd; //top node of the right end

    void makeLayersAndStuff(); //initializes layers and left and right side

	QuadNode* findNode(int key) const; //finds the node that has entry with given key
	QuadNode* greaterNode(int key) const; //finds the node that has entry with smallest key that is greater than the given key
	QuadNode* lessNode(int key) const; //finds the node that has entry with largest key that is smaller than the given key

public:
    SkipList(); //constructor
	~SkipList(); //destructor

    Entry* find(int key) const; //find the entry with the given key
    Entry* greaterEntry(int key) const; //find the entry with smallest key that is greater than the given key
    Entry* lessEntry(int key) const; //find the entry with largest key that is smaller than the given key

    void put(int key, string value); //add new entry or replace existing one
    void erase(int key); //clears based on key, error if key is not found

    int size() const; //get the amount of entries
    bool empty() const; //is size 0?

    void print(ostream& str) const; //print out the list to the specified stream (usually cout)
};