#include <iostream>
#include <string>

#include "Node.h"		// including Node header file


// constructor 
Node::Node(string &name, int num)
{
	ticker = name;						// initializing the ticker name
	numberOfShares = num;				// initializing the number of shares
	totalValueOfShare = 0;				// initializing total value of share 

	this->nextPtr = 0;
	this->previousPtr = 0;
}

