#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Account.h"
#include <iostream>

using namespace std;

class BankAccount : public Account			// public inheritance
{
public:
	void setBalance(double bal);
	double getBalance();
	void withdrawMoney(double money);
	void depositMoney(double money);
	virtual void printHistory();
	void storeHistory(string, double, tm *, double);
};


#endif