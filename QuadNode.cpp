#include "QuadNode.hpp"

QuadNode::QuadNode(QuadNode *left, Entry *entry) 
{
    this->left = left; //assign left

    if(left != nullptr) left->right = this; //this node becomes the right node of the given left

    this->entry = entry; //asign the entry
}

int QuadNode::getKey() const
{
	return entry->getKey(); //return the key from the entry
}

Entry * QuadNode::getEntry() const
{
	return entry;
}
