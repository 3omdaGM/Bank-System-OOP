#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsFindClientScreen : protected clsScreen
{
public:
	static void FindClient()
	{
		if (!_CheckPermission(clsUser::enPermissions::pFindClient))
		{
			return;
		}

		string Title = "\t  Find Client Screen";
		_DrawScreenHeader(Title);

		string AccountNumber;
		cout << "What is the Account Number? ";
		cin >> AccountNumber;
		cout << endl;
		if (clsBankClient::IsClientExist(AccountNumber))
		{
			clsBankClient Client = clsBankClient::Find(AccountNumber);
			Client.Print();
		}
		else
		{
			cout << "Account Number Not Exist" << endl;
		}
		
	}

};

