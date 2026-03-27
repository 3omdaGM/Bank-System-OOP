#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsDepositScreen: protected clsScreen
{

public:
	static void Deposit()
	{
		string Title = "\t\tDeposit Screen";
		_DrawScreenHeader(Title);

		
		cout << "which Account Number you wanna deposit to? ";
		string AccountNumber = clsInputValidate::ReadString();
		cout << endl;

		if (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account Number Not founded, please try another one the next time :) " << endl;
		}
		else
		{
			
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			cout << endl;
			Client.Print();

			cout << "\nHow much you wanna Deposit to <<" + Client.fname + ">> ?  ";
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
			}
		}


	}

};

