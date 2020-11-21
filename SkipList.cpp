#include "SkipList.hpp"
#include <vector>
#include <cstdlib>
#include <ctime>
#include "EntryException.hpp"

const int BIG = (int)2e9;

SkipList::SkipList() 
{
	srand(time(NULL)); //seed the random number so that it returns different results based on time
    makeLayersAndStuff(); //initialize left and right sides
}

SkipList::~SkipList() 
{
	cout << "Destructor of SkipList was called" << endl;

	/* could be used to delete nodes and entries if there was a need

	QuadNode *right = bottomOfLeftSide->right; //store the right side
	
	for(QuadNode *node = bottomOfLeftSide; right != nullptr; node = right) //traverse horizontally
	{
		Entry *entry = node->getEntry();

		delete entry; //delete the entry

		QuadNode *up = node->up;
		while(up != nullptr) //traverse vertically
		{
			delete node; //delete each node vertically
			node = up;
			up = node->up;
		}
		delete node; //delete the top node
	}

	*/
}

QuadNode * SkipList::findNode(int key) const
{
    QuadNode* node = topOfLeftGuy; //start traversing from top left corner

    while(node != nullptr) 
    {
        while(node->right->getKey() < key) node = node->right; //move right if less than key
        if(node->right->getKey() == key) return node->right; //return Entry if keys match
        node = node->down; //move to down layer
    }
    
    return topOfEnd; //return end because nothing was found
}

QuadNode * SkipList::lessNode(int key) const
{
	QuadNode* node = topOfLeftGuy; //start traversing from top left corner

	while (node->down != nullptr)
	{
		while (node->right->getKey() < key) node = node->right; //move right if less than key
		node = node->down; //move to down layer
	}
	while (node->right->getKey() < key) node = node->right; //one more time, move right if less than key

	if (node->right == nullptr) return topOfEnd; // could not find
	if (node->getKey() < key && node->right->getKey() >= key) return node; //found it
	else return topOfEnd; //could not find
}

QuadNode * SkipList::greaterNode(int key) const //find the lessOrEqualNode and take the node right after it
{
	QuadNode* found = findNode(key); //find the node with key equal to the passed key

	if(found != topOfEnd) //an entry with same key was found
	{
		if (found->right == topOfEnd) return topOfEnd; //this entry has nothing to its right so we found a dead end
		else return found->right; //we found what we're looking for
	}

	QuadNode* less = lessNode(key); //find the lessEntry node

	//if the lessEntry node is the end or if the node next to it is the end, then there is no greaterNode
	if (less->getEntry() == topOfEnd->getEntry() || less->right->getEntry() == topOfEnd->getEntry()) return topOfEnd;
	else return less->right; //we found what we were looking for
}

Entry* SkipList::find(int key) const
{
    return findNode(key)->getEntry(); //get the entry of findNode
}

Entry* SkipList::lessEntry(int key) const
{
	return lessNode(key)->getEntry(); //get the entry of lessNode
}

Entry* SkipList::greaterEntry(int key) const
{
	return greaterNode(key)->getEntry(); //get the entry of greaterNode
}

void SkipList::makeLayersAndStuff() 
{
	Entry* leftEntry = new Entry(-1, "This is the left side"); //create entry for left end
	Entry* rightEntry = new Entry(BIG, "This is the end"); //create entry for right end

    QuadNode *left = new QuadNode(nullptr, leftEntry); //create bottom left node
    QuadNode *right = new QuadNode(left, rightEntry); //create bottom right node

	bottomOfLeftSide = left; //assign bottom left node
	bottomOfEnd = right; //assign bottom right node

    for(int i = 0; i < layerCount; i++) //go through all layers
    {
        QuadNode *leftUp = new QuadNode(nullptr, leftEntry); //create top of current left node
        QuadNode *rightUp = new QuadNode(leftUp, rightEntry); //create top of current right node

        left->up = leftUp; //assign top of left node
        leftUp->down = left; //assign bottom of this new left node

        right->up = rightUp; //assign top of right mode
        rightUp->down = right; //assign bottom of this new right node

        left = leftUp; //repeat for new left
		right = rightUp; //repeat for new right
    }

    topOfLeftGuy = left; //assign top left node
    topOfEnd = right; //assign top right node
}

void SkipList::put(int key, string value) 
{
    Entry *found = find(key); //find entry with this key

    if(found != topOfEnd->getEntry()) found->setValue(value); //we found the entry so we just change its value
    else
    {
        vector<QuadNode*> path; //store nodes whose right sides might become this new node
        QuadNode* node = topOfLeftGuy; //start traversing nodes from top left

        while(node != nullptr) 
        {
            while(node->right->getKey() < key) node = node->right; //move right while getKey() is less than key
            path.push_back(node); //add the node we stopped at to path
            node = node->down; //move down
        }
        
        int height = rand() % layerCount + 1; //randomly determine the height of this new entry

        Entry* newEntry = new Entry(key, value); //create the new entry

        QuadNode* down = nullptr; //store the last node for assigning the up and down references

        for(int i = 0; i < height; i++) //traverse the height
        {
            QuadNode *left = path[path.size() - 1 - i]; //take a node from path as a left node for our new node
            
            QuadNode *right = left->right; //left node's right is now our new node's right

            QuadNode *newNode = new QuadNode(left, newEntry); //create the new node

            newNode->right = right; //assign left node's right to new node's right

            newNode->down = down; //new node's down is last node
            if(down != nullptr) down->up = newNode; //last node's up is new node
            down = newNode; //new node becomes down and the cycle will repeat on it
        }
    }
}

void SkipList::erase(int key)
{
	QuadNode *node = findNode(key); //find node to erase

	if (node->getEntry() == bottomOfEnd->getEntry()) //could not find
		throw new EntryException("Key you asked to delete does not exist!");

	Entry *entry = node->getEntry(); //we take the entry from the node since it's what we really want to remove

	while (node != nullptr) 
	{
		QuadNode* left = node->left; //take the previous left
		QuadNode* right = node->right; //take the previous right
		QuadNode* down = node->down; //take the bottom node because we'll need to remove it as well

		left->right = right; //left node's right becomes our right
		right->left = left; //right node's left becomes our left

		//delete node; //we could remove the node we were meant to erase

		node = down; //we do the same thing to lower layers of this node
	}

	//delete entry; //we could remove the entry as well
}

int SkipList::size() const 
{
	int count = 0;
	for (QuadNode* node = bottomOfLeftSide->right; node != bottomOfEnd; node = node->right) count++; //traverse nodes
	return count;
}

bool SkipList::empty() const
{
	return bottomOfLeftSide->right == bottomOfEnd; //if leftest connects to rightest, then the list is empty
}

void SkipList::print(ostream& str) const
{
	str << "-inf";

	for (QuadNode *node = bottomOfLeftSide->right; node != bottomOfEnd; node = node->right)
	{
		str << "--";
		if (node->getKey() < 10) str << "0"; //always occupy 2 letters (01 02 03 04 05 06 07 08 09 10 11 ...)
		str << to_string(node->getKey()); //write keys into it
	}

	str << "--inf";

	str << "\n"; //to end line, might consider removing this
}
