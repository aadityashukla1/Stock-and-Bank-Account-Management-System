#include <iostream>
#include "StockPortfolioAccount.h"
#include <ctime>
#include <fstream>
#include <string>
#include "DoublyLinkedList.h"

// set the cash balance
void StockPortfolioAccount::setBalance(double bal)
{
	cashBalance = bal;
}

// return the cash balance
double StockPortfolioAccount::getBalance()
{
	return cashBalance;
}


// print history of transaction
void StockPortfolioAccount::printPortfolio()
{
	// open the bank_transaction_history.txt and print it row by row
	ifstream inFile;	// create ifstream object to read the file
	string line;			// create a line to read from file

	if (!inFile.is_open())		// if file is not open then open it
	{
		inFile.open("stock_transaction_history.txt");		// opening the input file
	}

	if (inFile.peek() == std::ifstream::traits_type::eof())	// if file is empty
	{
		cout << "Stock transaction list is empty" << endl;	// display
	}
	else
	{
		cout << "Company-Symbol\t" << "Number\t" << "PricePerShare\t" << "TotalValue\t" << "Time\t" << endl;		// display

		while (!inFile.eof())		// print line by line
		{
			getline(inFile, line);					// get complete row from the file
			cout << line << endl;					// print line
		}

		inFile.close();				// close file

	}		// end else
}

// buy the stock and store the transaction in history
void StockPortfolioAccount::buy(string companyName, int numberOfStocks, double pps, tm *date)
{
	ofstream outputFile;			// create ofstream to object to write to file

	if (!outputFile.is_open())		// check if file is not open
	{
		outputFile.open("stock_transaction_history.txt", ios::app);		// open the file
	}

	//asctime_s(str, sizeof str, date );
	// write to file
	outputFile << "BUY" << "           " << companyName << " " << numberOfStocks << " " << "$" << pps << " " << "$" << pps*numberOfStocks << 
		" " << date->tm_hour << ":" << date->tm_min << ":" << date->tm_sec << endl;

	outputFile.close();		// close the output file
}


// sell the stock and store the transaction in history
void StockPortfolioAccount::sell(string companyName, int numberOfStocks, double pps, tm *date)
{
	ofstream outputFile;			// create ofstream to object to write to file

	if (!outputFile.is_open())		// check if file is not open
	{
		outputFile.open("stock_transaction_history.txt", ios::app);		// open the file
	}

	//asctime_s(str, sizeof str, date );
	// write to file
	outputFile << "SELL" <<" "<<companyName << " " << numberOfStocks << " " << "$" << pps << " " << "$" << pps*numberOfStocks <<
		" " << date->tm_hour << ":" << date->tm_min << ":" << date->tm_sec << endl;

	outputFile.close();		// close the output file
}




