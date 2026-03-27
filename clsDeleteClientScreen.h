#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;


class clsDeleteClientScreen : protected clsScreen
{
public:

   static void DeleteClient()
    {
       if (!_CheckPermission(clsUser::enPermissions::pDeleteClient))
       {
           return;
       }

        string Title = "\t  Delete Client Screen";
        _DrawScreenHeader(Title);

        string AccountNumber = " ";

        cout << "Enter the Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nthis Account Number is NOT exist, Please a real one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        cout << endl;

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        Client.Print();

        char DeleteChoise = ' ';

        cout << "\nAre you want sure that you wanna delete this client? y/n? " << endl;
        cin >> DeleteChoise;

        if (tolower(DeleteChoise) == 'y')
        {
            if (Client.Delete())
            {
                cout << "\n\nClient Deleted Successfully :((\n" << endl;
                Client.Print();
            }
        }
        else
        {
            cout << "\n\nClient Not Deleted :)" << endl;
        }

    }

};

