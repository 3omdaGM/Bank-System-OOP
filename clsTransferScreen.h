#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:


public:
	static void Transfer()
	{
		string Title = "\t\Transfer Screen";
		_DrawScreenHeader(Title);


		cout << "Enter which Account Number you wanna Transfer From? ";
		string AccountNumber1 = clsInputValidate::ReadString();

		if (!clsBankClient::IsClientExist(AccountNumber1))
		{
			cout << "\nAccount Number Not founded, please try another one the next time :) " << endl;
		}
		else
		{

			clsBankClient Client1 = clsBankClient::Find(AccountNumber1);
			cout << endl;
			Client1.MiniPrint();

			/*cout << "\nHow much you wanna Deposit to <<" + Client.fname + ">> ?  ";
			double DepositAmount = clsInputValidate::ReadDblNumber();
			char Choise;
			cout << "\nAre u sure that you wanna Deposite (" << DepositAmount << ") to <<" + Client.fname + ">> ? y/n?  ";
			cin >> Choise;
			cout << endl;

			if (tolower(Choise) == 'y')
			{
				Client.Deposit(DepositAmount);
				cout << "\n Deposit Done Successfully :)" << endl;
			}
			else
			{
				cout << "Failed Deposit Operation." << endl;
			}*/

			cout << "\nEnter which Account Number you wanna Transfer To? ";
			string AccountNumber2 = clsInputValidate::ReadString();

			if (!clsBankClient::IsClientExist(AccountNumber2))
			{
				cout << "\nAccount Number Not founded, please try another one the next time :) " << endl;
			}
			else
			{
				clsBankClient Client2 = clsBankClient::Find(AccountNumber2);
				cout << endl;
				Client2.MiniPrint();


				float Amount;
				cout << "\nEnter Transfer Amount? ";
				cin >> Amount;
				
				while (Amount > Client1.AccountBalance)
				{
					cout << "\n\nAmount Exceeds the available Balance, Enter another Amount?  ";
					cin >> Amount;
				}
				cout << "\nAre you sure that you wanna do this operation? y/n?  ";
				char Choise;
				cin >> Choise;
				if (tolower(Choise) == 'y')
				{
					if (Client1.Transfer(Client2, Amount, CurrentUser.UserName))
					{
						cout << "\n\nTransfer Done :)\n";
						cout << "You transferd (" << Amount << ") from <<" + Client1.FullName() + ">> to <<" + Client2.FullName() + ">> .\n" << endl;
					}
					else
					{
						cout << "\nOperation Failed!" << endl;
					}
				}
				else
				{
					cout << "\nOperation Failed!" << endl;
				}
				cout << "\n\nNew Info Now is: \n\n";
				Client1.MiniPrint();
				cout << endl;

				Client2.MiniPrint();
				cout << endl;

				

			}

		}


		




	}

};

