#include "DoublyLinkedList.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>


using namespace std;

// constructor
DoublyLinkedList::DoublyLinkedList()
{
	headPtr = 0;		// initializing the headPtr to zero
	tailPtr = 0;		// initializing the tailPtr to zero
}

// desctructor
DoublyLinkedList::~DoublyLinkedList()
{
	if (!isListEmpty())				// check if list is not empty
	{
		Node *currentPtr = headPtr;			//  make a new node pointer which is pointing to headPtr
		Node *tempPtr;						// create a tempPtr

		while (currentPtr != 0)		// iterate untill currentPtr is pointing to null
		{
			tempPtr = currentPtr->nextPtr;	// increment currentPtr node and copy it to tempPtr
			delete currentPtr;				// delete the tempPtr node
			currentPtr = tempPtr;			// copy tempPtr to currentPtr			
		}
	}
}

// function to check if the list is empty
bool DoublyLinkedList::isListEmpty()
{
	if (headPtr == 0)	// if headPtr is zero
		return true;	// list is empty and return true
	else
	{
		return false;			// list is not empty
	}
}

// function to add node at the end of the string
void DoublyLinkedList::addToEnd(string &name, int value)
{
	Node *newPtr = getNewNode(name, value);		// get a new node
	
	if (isListEmpty())		// check if list is empty
	{
		headPtr = tailPtr = newPtr;
	}
	else				// list is not empty
	{
		Node *tempPtr;
		tempPtr = tailPtr;
		tailPtr->nextPtr = newPtr;
		newPtr->previousPtr = tailPtr;
		tailPtr = newPtr;
	}
}

// function to get a new node space and return the pointer node object
Node* DoublyLinkedList::getNewNode(string&name, int value)
{
	return new Node(name, value);
}

// print the list
void DoublyLinkedList::print(unordered_map<string, double> &map, double cashBal) 
{
	double totVal = 0;
	if (isListEmpty())
	{
		cout << "List is empty" << endl;
	}
	else
	{
		Node *currentPtr = headPtr;
		cout << "Ticker         Number    Price per share	TotalValue" << endl;
		while (currentPtr != 0)
		{
		 totVal += ( map.at(currentPtr->ticker) * currentPtr->numberOfShares) ;
			cout << currentPtr->ticker << "              " << currentPtr->numberOfShares <<
				"		"<< map.at(currentPtr->ticker) <<"		" << map.at(currentPtr->ticker) * currentPtr->numberOfShares <<endl;
			// increment
			currentPtr = currentPtr->nextPtr;
		}
	}
	cout << "Total portfolio value: " << totVal + cashBal << endl;
}

// check if the stock is in the list
bool DoublyLinkedList::isInList(string &name, int num)
{
	Node *currentPtr = headPtr;

	if (isListEmpty())				// if list is empty return false
		return false;

	while (currentPtr != 0)			// traverse till end of the list
	{
		if (currentPtr->ticker == name && currentPtr->numberOfShares >=num)
			return true;					
		currentPtr = currentPtr->nextPtr;				// increment the currentPtr
	}
	return false;	// inputted stock does not exists or number of stocks are not equal
}

// check for perfect match  (ticker == name && numberOfShares =num)
bool DoublyLinkedList::checkMatch(string &name, int num)
{
	Node *currentPtr = headPtr;
	Node *tempPtr;					// tempPtr
	Node *nw;

	if (isListEmpty())				// if list is empty return false
		return false;

	while (currentPtr != 0)			// traverse till end of the list
	{
		if (currentPtr->ticker == name && currentPtr->numberOfShares == num)
		{
			if (headPtr == tailPtr)			// if there is only element in the linked list
			{
				//delete currentPtr;
				headPtr = 0;				// make head and tail ptr to NULL
				tailPtr = 0;
				return true;
			}
			else
			{
				// check if it is last element
				if (tailPtr->ticker == name)
				{
					nw = tailPtr->previousPtr;
					nw->nextPtr = 0;
					tailPtr->previousPtr = 0;
					tailPtr = nw;
					return true;
				}
				 else if(headPtr->ticker == name)
				{
					tempPtr = currentPtr->nextPtr;
					tempPtr->previousPtr = NULL;
					headPtr = tempPtr;
					delete currentPtr;
					return true;
				}
				else
				{	
					tempPtr = currentPtr->previousPtr;			// copy currentPtr to tempPtr
					tempPtr->nextPtr = currentPtr->nextPtr;
					nw = currentPtr->nextPtr;
					nw->previousPtr = tempPtr;
					delete currentPtr;
					return true;
				}

			}

		}			// end of if statment for  delete

		currentPtr = currentPtr->nextPtr;				// increment the currentPtr
	}		// end of while condition	

	return false;	// inputted stock does not exists or number of stocks are not equal
}

// reduce number of stock as per contract
bool DoublyLinkedList::reduceNumStock(string &name, int num)
{
	Node *currentPtr = headPtr;

	if (isListEmpty())				// if list is empty return false
		return false;

	while (currentPtr != 0)			// traverse till end of the list
	{
		if (currentPtr->ticker == name && currentPtr->numberOfShares >= num)
		{
			currentPtr->numberOfShares = currentPtr->numberOfShares - num;
			return true;
		}
			
		currentPtr = currentPtr->nextPtr;				// increment the currentPtr
	}
	return false;	// inputted stock does not exists or number of stocks are not equal
}

// save the double link list to "stock_portfolio.txt"
void DoublyLinkedList::saveStockPortfolio()
{
	ofstream dllNew;										//	create a ofstream object
	dllNew.open("stock_portfolio.txt", ios::trunc);			// open the "stock_portfolio.txt" in truncate mode

	if (isListEmpty())
	{
		cout << "List is empty" << endl;
	}
	else
	{
		Node *currentPtr = headPtr;								// declare

		while (currentPtr != 0)									// traverse till the end of doubly linked list
		{
			dllNew << currentPtr->ticker << " " << currentPtr->numberOfShares;		// print to file
			currentPtr = currentPtr->nextPtr;													// increment the pointer
			if (currentPtr !=0)
			{
				dllNew << endl;
			}
		}		// end of while
	}	// end of else
	dllNew.close();												// close the file
}			// end of function

// update the linked list if the stock is already in the porfolio
// update the number of shares

bool DoublyLinkedList::updateLinkedList(string &name, int num)
{
	Node *currentPtr = headPtr;

	if (isListEmpty())
	{
		return false;
	}
	else
	{
		while ( currentPtr!= 0 )
		{
			if (currentPtr->ticker == name)
			{
				currentPtr->numberOfShares = currentPtr->numberOfShares + num;
				return true;
			}
			currentPtr = currentPtr->nextPtr;
		}		// end of while statement
	}			// end of else statement
	return false;
}				// end of function

// Function to return total portfolio value
double DoublyLinkedList::stockPortfolioValue(unordered_map <string, double> &map)
{
	double totVal = 0;

		Node *currentPtr = headPtr;
		
		while (currentPtr != 0)
		{
			totVal += (map.at(currentPtr->ticker) * currentPtr->numberOfShares);
			// increment
			currentPtr = currentPtr->nextPtr;
		}	
	return  totVal ;		// return total stock portfolio value
}

// calculate the total value of share and store it in each node
void DoublyLinkedList::totalValueCalculation(unordered_map <string, double> &newUmap)
{
	double totVal = 0;

	Node *currentPtr = headPtr;

	while (currentPtr != 0)
	{
		currentPtr->totalValueOfShare= (newUmap.at(currentPtr->ticker) * currentPtr->numberOfShares);
		// increment
		currentPtr = currentPtr->nextPtr;
	}
	
}

// sort the doubly linkedlist based on total value
void DoublyLinkedList::sort( )
{
	int count = 0;

	Node *currentPtr = headPtr;
	while (currentPtr != NULL)
	{
		count++;
		currentPtr = currentPtr->nextPtr;
	}

	currentPtr = headPtr;

	if (headPtr != NULL)
	{
		Node* prev = 0;
		Node *tempPtr = NULL;
		int swap = 0;
		for (int i = 0; i < count; i++)
		{
			while (currentPtr->nextPtr != 0)
			{
				tempPtr = currentPtr->nextPtr;

				if (currentPtr->totalValueOfShare < tempPtr->totalValueOfShare)
				{
					tempPtr->previousPtr = currentPtr->previousPtr;
					currentPtr->previousPtr = tempPtr;
					swap = 1;
					currentPtr->nextPtr = tempPtr->nextPtr;
					if (currentPtr->nextPtr != NULL)
						currentPtr->nextPtr->previousPtr = currentPtr;						
					tempPtr->nextPtr = currentPtr;
					if (prev != 0)
						prev->nextPtr = tempPtr;
					prev = tempPtr;
					if (headPtr == currentPtr)
						headPtr = tempPtr;
					if (currentPtr->nextPtr == 0)
						tailPtr = currentPtr;
				}
				else
				{
					prev = currentPtr;
					currentPtr = currentPtr->nextPtr;
				}
			}
			if (swap == 0)
				break;
			else
			{
				prev = 0;
				currentPtr = headPtr;
				swap = 0;
			}
		}
	}
}			// end of sort function

