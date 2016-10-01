#include <iostream>
#include "BankAccount.h"
#include <ctime>
#include <fstream>
#include <string>

// set the cash balance
void BankAccount::setBalance(double bal)
{
	cashBalance = bal;
}

// return the cash balance
double BankAccount::getBalance()
{
	return cashBalance;
}

// withdraw money method
void BankAccount::withdrawMoney(double money)
{
	cashBalance = cashBalance - money;

}

// deposit money method
void BankAccount::depositMoney(double money)
{
	cashBalance = cashBalance + money;
}

// print history of transaction
void BankAccount::printHistory()
{			
		// open the bank_transaction_history.txt and print it row by row
		ifstream inFile;	// create ifstream object to read the file
		string line;			// create a line to read from file

		if (!inFile.is_open() )		// if file is not open then open it
		{
			inFile.open("bank_transaction_history.txt");		// opening the input file
		}

		 if( inFile.peek() == std::ifstream::traits_type::eof() )	// if file is empty
			{
				cout << "Bank transaction list is empty" << endl;	// display
			}
		 else
		 {
			 cout << "Event\t" << "Amount\t" << "Date\t" << "Balance\t" << endl;		// display

			 while (!inFile.eof())		// print line by line
			 {
				 getline(inFile, line);					// get complete row from the file
				 cout << line << endl;					// print line
			 }

			 inFile.close();				// close file

		 }		// end else
}

// store the history into .txt file
void BankAccount::storeHistory(string eventType, double amount_value, tm *date, double balance_value)
{	
	ofstream outputFile;			// create ofstream to object to write to file

	if (!outputFile.is_open())		// check if file is not open
	{
		outputFile.open("bank_transaction_history.txt", ios::app);		// open the file
	}

	//asctime_s(str, sizeof str, date );
	// write to file
	outputFile << eventType << " " <<"$" << amount_value << " " << date->tm_mon <<"/" << date->tm_mday << "/" << 1900+date->tm_year << " "  << "$" << balance_value << endl;
	
	outputFile.close();		// close the output file
}