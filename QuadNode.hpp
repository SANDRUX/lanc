#pragma once

#include "Entry.hpp"

class QuadNode
{
    Entry *entry;

public:
    QuadNode *left, *right, *up, *down; //pointers to neighboring nodes

    QuadNode(QuadNode *left, Entry *entry); //constructor

    int getKey() const; //get the key from the entry
    Entry* getEntry() const;
};