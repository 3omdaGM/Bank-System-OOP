#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
{
public:
	static void FindUser()
	{
		string Title = "\t  Find User Screen";
		_DrawScreenHeader(Title);

		string UserName;
		cout << "What is the User Name? ";
		cin >> UserName;
		cout << endl;
		if (clsUser::IsUserExist(UserName))
		{
			clsUser User = clsUser::Find(UserName);
			User.Print();
		}
		else
		{
			cout << "User Name is Not Exist" << endl;
		}

	}

};

