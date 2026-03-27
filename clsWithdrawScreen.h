#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
{
public:

	static void Withdraw()
	{
		string Title = "\t\Withdraw Screen";
		_DrawScreenHeader(Title);


		cout << "which Account Number you wanna Withdraw from? ";
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

			cout << "\nHow much you wanna Withdraw from <<" + Client.fname + ">> ?  ";
			double WithdrawAmount = clsInputValidate::ReadDblNumber();

			while (WithdrawAmount > Client.AccountBalance)
			{
				cout << "\nCannot Withdraw , The Amount of Withdraw is bigger than the current Balance which exist in  <<" + Client.fname +
					">> \nPlease Enter a less Amount ---->  ";
				WithdrawAmount = clsInputValidate::ReadDblNumber();
			}
			cout << endl;
			char Choise;
			cout << "\nAre u sure that you wanna Withdraw (" << WithdrawAmount << ") to <<" + Client.fname + ">> ? y/n?  ";
			cin >> Choise;
			cout << endl;

			if (tolower(Choise) == 'y')
			{
				Client.Withdraw(WithdrawAmount);
				cout << "\n Withdraw Done Successfully :)" << endl;
			}
			else
			{
				cout << "Failed Withdraw Operation." << endl;
			}
		}


	}

};

