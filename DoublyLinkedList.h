#ifndef DOUBLYLINKEDLIST_H
#define	DOUBLYLINKEDLIST_H
#include <string>
#include <unordered_map>
#include "Node.h"			// including Node header file

using namespace std;

class DoublyLinkedList
{
public:
	
	DoublyLinkedList();
	~DoublyLinkedList(); 
	bool isListEmpty();
	void addToEnd(string &name, int);
	void print( unordered_map <string, double> &map, double cashBal) ;
	bool isInList(string& name, int);
	bool checkMatch(string &name, int num);
	bool reduceNumStock(string &symbol, int numOfShares);
	void saveStockPortfolio();
	bool updateLinkedList(string &symbol, int numOfShares);
	double stockPortfolioValue(unordered_map <string, double> &map);
	void totalValueCalculation(unordered_map <string, double> &newUmap);
	void sort();

	
	

private:
	Node *headPtr;
	Node *tailPtr;
	Node* getNewNode(string&, int);

};	// end class 

#endif

