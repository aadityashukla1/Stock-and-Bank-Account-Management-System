
#include <iostream>	
#include "Account.h"
#include "Node.h"
#include "DoublyLinkedList.h"
#include "BankAccount.h"
#include "StockPortfolioAccount.h"
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>
#include <sstream>
#include <ctime>


#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )   
#pragma comment( lib, "libeng.lib" )

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
// end
// end
#include<engine.h>

void loadFile();
// storing the text file data in Hash table

unordered_map<string, double> umap;		// declaring a unordered map to store the input file data
unordered_map<string, double>::const_iterator found;		// iterator for Hash Map
string line, a;			// declaring line and a;
double b;				// declaring b


using namespace std;

int main()
{
	string symbol;			// company stock symbol
	double val;				
	double cashBal;			// variable for cashBalance
	int choice;				// user choice	
	const int def = 10000;	// default cashBalance value
	int numOfShares;		// stock number of shares
	double maxPrice;		// max price user is willing to pay to buy stock
	double minPrice;			// min price user is willing to pay to sell stock
	double totalBal;

	BankAccount ba;		// create object of class BankAccount
	double am;			// declare amount variable which will be used by class BankAccount

	StockPortfolioAccount spa;		// create object of class Stock Portfolio Account

	DoublyLinkedList dll;			// create  dll

	time_t t;			// create a time_t object
	struct tm  buf;		// create a tm object which stores all the calendar information


	//------------------------ Step 1 - load the stock text file data into hash table-----------------------------


	loadFile();


	// -----------------------Step 2 - Load the cashBalance value from .txt file-----------------------------------
	{	// start of block statement

		ifstream inCash("cash_balance.txt");						// create ifstream object
		ofstream cas;

		if (inCash.good())	// if file exists
		{
			//inCash.open("cash_balance.txt", ios::in);		// open the file
			getline(inCash, line);					// get the line
			stringstream ss(line);					// store it in stringstream
			ss >> cashBal;							// retireve the cashBalance
			ba.setBalance(cashBal);					// set the cashBalance
			inCash.close();
		}
		// if file is not created then create a new cash_balance.txt file and store 10000
		else
		{
			cas.open("cash_balance.txt", ios::out);		// open the file
			cas << def;									// store 10,000
			cas.close();									// close connection
		}		
	}		// end of block statement

	//-----------------------Step 3 - Load the stock portfolio in Double Linked List----------------------------

	{	// start of block statement
		ifstream inList("stock_portfolio.txt");						// create ifstream object
		ofstream cas1;

		if (inList.good())	// if file exists
		{
			//inCash.open("stock_portfolio.txt", ios::in);			// open the file
			while (!inList.eof())									// till end of the file
			{

					getline(inList, line);									// get the line
					stringstream ss(line);									// store it in stringstream
					ss >> symbol >> numOfShares;							// retireve the stock portfolio data
					if(numOfShares > 0)
					dll.addToEnd(symbol, numOfShares);						// add to Double Linked List	
				
			}
			inList.close();
		}
		else
		{
			cas1.open("stock_portfolio.txt", ios::out);
			cas1.close();
		}
	}

	//----Step 4 - Display the main menu which will be displayed to the users---------------------------------------

	// Display the menu and display this menu again if the user wants to execute another choice
	do {										
		// Display statement
		cout << "Welcome to the Account Management System." << endl;
		cout << "Please select an account to access:" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		
		cout << "Option: ";
		cin >> choice;		// user choice in account management system menu

		switch (choice)			// start of switch statement		
		{

	// Stock Portfolio Account
		case 1:
			int ch;			// declare choice which will be used by switch statement in Stock Portfolio Account
			
		   // Display the menu and display this menu again if the user wants to execute another choice
			do
			{
				// Display Statment
				cout << "Stock Portfolio Account" << endl;
				cout << "Please select an option:" << endl;
				cout << "1. Display the price for a stock symbol" << endl;
				cout << "2. Display the current portfolio" << endl;
				cout << "3. Buy shares" << endl;
				cout << "4. Sell shares" << endl;
				cout << "5. View a graph for the portfolio value" << endl;
				cout << "6. View transaction history" << endl;
				cout << "7. Sort the portfolio" << endl;
				cout << "8. Return to previous menu" << endl;
				
				cout << "Option: ";
				cin >> ch;				// user choice in Stock Porfolio Account menu

				switch (ch)		// switch statement for Stock portfolio account menu
				{
				// Display the price for a stock symbol
				case 1:
					cout << "Please enter the stock symbol: ";		// enter the stock symbol
					cin >> symbol;									// store the symbol

					// select a file randomly between two Result.txt files
					loadFile();
					// check if the entered stock symbol is valid
					found = umap.find(symbol);

					if (found == umap.end() )
					{
						cout << "You have entered an invalid Stock name" << endl;						
					}
					else
					{
						val = umap.at(symbol);													// call the umap with key value and store the value
						cout << "Company price per share" << endl << val << "$" << endl;		// display
					}
					break;

				// Display the current portfolio
				case 2:		
					cashBal = ba.getBalance();
					cout << "Cash Balance is: " << cashBal << endl;

					// select a file randomly between two Result.txt files
					loadFile();

					dll.print(umap, cashBal);
					
						break;				

				// Buy shares
				case 3:
					// Display and accept user input
					cout << "Please enter the stock symbol you wish to purchase: ";
					cin >> symbol;

					// select a file randomly between two Result.txt files
					loadFile();

					// check if the entered stock name is valid
					found = umap.find(symbol);

					if (found == umap.end())
					{
						cout << "You have entered an invalid Stock name" << endl;
					}
					else
					{
						cout << "Please enter the number of shares: ";
						cin >> numOfShares;
						cout << "Please enter the maximum amount you are willing to pay per share: ";
						cin >> maxPrice;

						val = umap.at(symbol);						// retreive the present value of stock

																	// check if user has appropriate cashBalance to execute the buy contract
						if ((val*numOfShares) <= spa.getBalance())
						{
							// check if max price is within the range						
							if (val <= maxPrice)
							{

								t = time(NULL);				// call time() function to get the time in seconds
								localtime_s(&buf, &t);		// store the time value as calendar value in tm object which is buf

								spa.buy(symbol, numOfShares, val, &buf);		// save the transaction info to .txt file

								// check if the entered stock is already in the portfolio
								// if it is already in the portfolio then update the link list 
								if (dll.isInList (symbol, 0) )
								{
									dll.updateLinkedList(symbol, numOfShares);	
								}
								else
								{
									dll.addToEnd(symbol, numOfShares);		// add the transaction detail to linked List
								}
																		// save the double linked list in .txt file
								dll.saveStockPortfolio();

								// Display
								cout << "You have purchased " << numOfShares << " shares of " << symbol << " at "
									<< "$" << val << " each for a total of $" << val*numOfShares << endl;

								ba.withdrawMoney(val*numOfShares);		// subtract the money from cashBalance
							}
							else
							{
								cout << "Transaction failed since entered maximum price is less than current value of stock" << endl;
							}
						}
						else
						{
							cout << "Transaction failed since the available balance is less than amount needed to execute the contract" << endl;
						}
					}			

					break;

				// Sell shares
				case 4:
					// Display and accept user input
					cout << "Please enter the stock symbol you wish to sell: ";
					cin >> symbol;

					// select a file randomly between two Result.txt files
					loadFile();
					// check if the entered stock name is valid
					found = umap.find(symbol);

					if (found == umap.end())
					{
						cout << "You have entered an invalid Stock name" << endl;
					}
					else
					{
						cout << "Please enter the number of shares: ";
						cin >> numOfShares;
						cout << "Please enter the minimum amount you are willing to pay per share: ";
						cin >> minPrice;

						val = umap.at(symbol);						// retreive the present value of stock

																	// check if user has stock and their appropriate number of stocks

						if (dll.isInList(symbol, numOfShares))
						{
							// check if min price is within the range						
							if (val >= minPrice)
							{
								t = time(NULL);				// call time() function to get the time in seconds
								localtime_s(&buf, &t);		// store the time value as calendar value in tm object which is buf

								spa.sell(symbol, numOfShares, val, &buf);		// save the transaction info to .txt file

																		// reduce the number of stocks or delete the complete row if all the stocks are sold
								if (dll.checkMatch(symbol, numOfShares))
								{
								}
								else
								{
									dll.reduceNumStock(symbol, numOfShares);
								}

								// save the updated portfolio in "stock_portfolio.txt"
								// save the double linked list in .txt file
								dll.saveStockPortfolio();

								// Display
								cout << "You have sold " << numOfShares << " shares of " << symbol << " at "
									<< "$" << val << " each for a total of $" << val*numOfShares << endl;

								ba.depositMoney(val*numOfShares);		// subtract the money from cashBalance
							}
							else
							{
								cout << "Transaction failed since entered stock sell price is more than the current stock price" << endl;
							}
						}
						else
						{
							cout << "Transaction failed since entered stock is not present in the portfolio or the" <<
								" number of stocks are more than the number of stocks in the portfolio" << endl;
						}
					}
					
					break;

				// View a graph for the portfolio value
				case 5:
				{
					// get the count in the file
					double x[11] = { 0 };
					string y[11];
					double ca = 0;
					string tim;
					ifstream plot;					// create ifstream object
					plot.open("TotalPortfolioValueDate.txt");
					int i = 0;
					while (!plot.eof())		// print line by line
					{						
						getline(plot, line);					// get the line
						stringstream ss1(line);					// store it in stringstream
						ss1 >> ca >> tim;							// retireve the cashBalance and date
						x[i] = ca;
						y[i] = tim;
						i++;
					}
					plot.close();
					
					Engine *ep;					
					ep = engOpen(NULL);					


					mxArray *A;
					A = mxCreateDoubleMatrix(1, 10, mxREAL);
					memcpy((void *)mxGetPr(A), (void *)x, 10*sizeof(double));
					engPutVariable(ep, "x", A);
					

					//mxArray *B;
					//B = mxCreateDoubleMatrix(1, 10, mxREAL);
					//memcpy((void *)mxGetPr(B), (void *)y, 10 * sizeof(string));
					//engPutVariable(ep, "y", B);

					engEvalString(ep, "X=x;");
					//engEvalString(ep, "Y=y;");
					engEvalString(ep, "plot(X);");	//call plot function
					//engEvalString(ep1, "plot(Y);");	//call plot function

					//engEvalString(ep, "X=x;Y=y");
					//engEvalString(ep, "plot(Y,X);");	//call plot function



					//engEvalString(ep, "title('Successful!!!');");

					mxDestroyArray(A);
					//mxDestroyArray(B);					

					break;
				}

				// View transaction history
				case 6:
					spa.printPortfolio();
					break;

				// sort
				case 7:
					loadFile();
					dll.totalValueCalculation(umap);
					dll.sort();
					dll.print(umap,ba.getBalance());
					break;
				
				//// Terminate the Stock Porfolio Menu
				case 8:
					break;

				// Default case
				default:
					cout << "You have entered an invalid number" << endl;
					break;

				}		// end of switch statement of Stock Portfolio Account menu

			} while (ch != 8);				// go back to Stock Portfolio Account menu

			break;		// terminate the Stock Potfolio menu and go back to main menu


	// Bank Account
		case 2:
			int ch1;		// declare choice which will be used by switch statement in Bank Account

			// Display the menu and display this menu again if the user wants to execute another choice
			do
			{
				// Display Statment
				cout << "Bank Account" << endl;
				cout << "Please select an option :" << endl;
				cout << "1. View account balance" << endl;
				cout << "2. Deposit money" << endl;
				cout << "3. Withdraw money" << endl;
				cout << "4. Print out history" << endl;
				cout << "5. Return to previous menu" << endl;

				cout << "Option: ";
				cin >> ch1;					// User choice in Bank Account menu

				switch (ch1)				// switch statement for Bank Account menu
				{
				// View account balance
				case 1:
					cout << "Account Balance is " << ba.getBalance() << endl;				// get the Cash Balance and display it
					break;

				// Deposit money
				case 2:
					cout << " Enter the amount which has to be deposited: " << endl;		// display
					cin >> am;					// input the user amount
					ba.depositMoney(am);		// call deposit method to add the amount to cash balance

					t = time(NULL);				// call time() function to get the time in seconds
					localtime_s(&buf, &t);		// store the time value as calendar value in tm object which is buf
					
					ba.storeHistory("Deposit", am, &buf, ba.getBalance());					// save the transaction in .txt file
					break;

				// Withdraw money
				case 3:
					cout << "Enter the amout to be withdrawn: " << endl;					// display
					cin >> am;																// input the user amount

					ba.withdrawMoney(am);								// subtract amount from cash balance

					t = time(NULL);										// call time() function to get the time in seconds
					localtime_s(&buf, &t);				// store the time value as calendar value in tm object which is buf

					ba.storeHistory("Withdraw", am, &buf, ba.getBalance());			// save the transaction in .txt file
					break;

				// Print out history
				case 4:
					ba.printHistory();					// print the history which is stored in .txt file
					break;

				// Return to previous menu
				case 5:
					break;

				// Default case
				default:
					cout << "You have entered an invalid choice" << endl;
					break;
	
				}								// end of swithc statment for bank account menu

			} while (ch1 != 5);					// Go back to Bank Account menu 

			break;								// terminate the Bank Account menu and go back to main menu

	// Terminate the program
		case 3:
			break;								// terminate the program 

	// Default option if the user has entered an invalid choice
		default:
			cout << "You have entered an invalid choice" << endl;
			break;

		}	// end of switch statement

	} while (choice != 3);						// Go back to do statment which is to ask user to input his choice again 


	// Before exit, save the cashBalance value in .txt file
	cashBal = ba.getBalance();							// get the value
	ofstream cash;										// create ofstream object
	cash.open("cash_balance.txt", ios::trunc);			// open the file 
	cash << cashBal;									// write to the file
	cash.close();										// close the file


	//--------------- Before exit, save the total portfolio value in TotalPortfolioValue.txt---------------------

	ofstream totalPort;						// create ofstream object
	
		totalPort.open("TotalPortfolioValue.txt", ios::trunc);				// open the file
		totalBal = dll.stockPortfolioValue(umap) + ba.getBalance();
		totalPort << totalBal;												
		totalPort.close();													// close connection

	//--------------- Before exit, save the total portfolio value in TotalPortfolioValueWithDate.txt---------------------
		{	// start of block statement

			ifstream totalPortDatei("TotalPortfolioValueDate.txt");						// create ifstream object
			ofstream totalPortDateo;
			string dat;
			t = time(NULL);				// call time() function to get the time in seconds
			localtime_s(&buf, &t);		// store the time value as calendar value in tm object which is buf
			tm *d = &buf;
			string comDate = to_string (d->tm_mon)+ "/" + to_string (d->tm_mday);
			double oldCash = 0;
			double necash =0;
			double totalBal1 = dll.stockPortfolioValue(umap) + ba.getBalance();
			map <double, string> map1;
			map<double, string>::iterator it;		// iterator for Hash Map
			int dup = 0;

			if (totalPortDatei.good())	// if file exists
			{			
				// store the existing file data into map
				while (!totalPortDatei.eof())		
				{
					getline(totalPortDatei, line);					// get the line
					stringstream ss1(line);					// store it in stringstream
					ss1 >> oldCash >> dat;							// retireve the cashBalance and date
					map1[oldCash] = dat;
				}
				totalPortDatei.close();
				
				totalPortDateo.open("TotalPortfolioValueDate.txt", ios::trunc);
				for (it = map1.begin(); it != map1.end(); it++)
				{
					if (comDate == it->second)
					{
						dup++;
						totalPortDateo << dll.stockPortfolioValue(umap) + ba.getBalance() << " " << comDate << endl;
					}
					else
					{
						totalPortDateo << it->first << " " << it->second << endl;
					}
				}
				if (dup == 0)
					totalPortDateo << dll.stockPortfolioValue(umap) + ba.getBalance() << " " << comDate << endl;
				totalPortDateo.close();
				// close connection
			}
		}

	return 0;		// successful termination;
}		// end of main



// load file function definition
void loadFile()
{
	// selecting a file randomly between two Result.txt files
	int x = 0;
	srand((int)time(NULL));
		x = rand() % 2 + 1;
	// create a fstream object to read the file contents and then store it in umap
	fstream myFile;
	// opening the input file
	if (x == 1)
	{
		myFile.open("D:/grad_books/programming finance/project/Results_1.txt");
	}
	else
	{
		myFile.open("D:/grad_books/programming finance/project/Results_2.txt");
	}

	// read line by line till the end of the file
	while (!myFile.eof())
	{
		getline(myFile, line);		// store the the extracted line from myFile
		stringstream ss(line);		// create string stream object and initialize it to line
		ss >> a >> b;				// extract the string object and store it in variables
		umap[a] = b;			// store the values in unordered map
	}

	myFile.close();			// closing the input file
}