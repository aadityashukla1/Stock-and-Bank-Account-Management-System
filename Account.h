#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>

using namespace std;

class Account
{
protected:
	double cashBalance = 10000;			// declaring the cashBalance variable
public:
	virtual void setBalance(double bal) = 0;
	virtual double getBalance() = 0;
	
};

#endif
