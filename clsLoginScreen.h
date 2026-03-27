#pragma once
#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
#include "clsInputValidate.h"
#include "clsString.h"

class clsLoginScreen : protected clsScreen
{
private:

	static bool _Login()
	{
		string Username;
		string Password;

		bool LoginState= false;
		short NumOfTries = 0;

		do 
		{
			cout << "Enter Username? ";
			Username = clsInputValidate::ReadString();

			cout << endl;

			cout << "Enter Password? ";
			Password = clsInputValidate::ReadString();

			CurrentUser = clsUser::Find(Username, Password);
			if (CurrentUser.IsEmpty())
			{
				NumOfTries++;
				if (NumOfTries == 3)
				{
					cout << "\nPlease try again later, your tries had been ended" << endl << endl;
					/*exit(0);*/
					return false;
				}
				cout << "\nInvalid Username/Password! you got "<<NumOfTries<<" of 3 tries and after 3 tries the Program would close '-'" << endl;
			}
			else
			{
				LoginState = true;
				
			}

			cout << endl;
			
		} while (LoginState==false/*&&NumOfTries<3*/);

		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();

	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\tLogin Screen");
		
		return _Login();

	}

	

};

