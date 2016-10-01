#ifndef NODE_H
#define	NODE_H
#include <string>
#include <iostream>

using namespace std;
class Node
{
	friend class DoublyLinkedList;
public:
	Node(string&, int);
	

private:
	int numberOfShares;
	string ticker;
	double totalValueOfShare;
	Node *nextPtr;
	Node *previousPtr;

};	// end class Node

#endif
