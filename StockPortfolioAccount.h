#ifndef STOCKPORTFOLIOACCOUNT_H
#define STOCKPORTFOLIOACCOUNT_H

#include "Account.h"
#include <iostream>

using namespace std;

class StockPortfolioAccount : public Account			// public inheritance
{
public:
	void setBalance(double bal);
	double getBalance();
	void printPortfolio();	
	void buy(string, int, double, tm *);
	void sell(string, int, double, tm *);
	
	
};


#endif
