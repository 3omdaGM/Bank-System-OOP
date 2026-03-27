#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateClientScreen: clsScreen
{
private:

    static void _ReadClientInfo(clsBankClient& Client)
    {

        cout << "Enter the new First Name : ";
        Client.fname = clsInputValidate::ReadString();

        cout << "Enter the new Last Name : ";
        Client.lname = clsInputValidate::ReadString();

        cout << "Enter the new Email     : ";
        Client.email = clsInputValidate::ReadString();

        cout << "Enter the new Phone     : ";
        Client.phone = clsInputValidate::ReadString();

        cout << "Enter the new PinCode   : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Enter the new Balance   : ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();

    }

public:
	

  static void UpdateClient()

    {

      if (!_CheckPermission(clsUser::enPermissions::pUpdateClients))
      {
          return;
      }
      string Title = "\t  Update Client Screen";
      _DrawScreenHeader(Title);

        cout << "Enter Account Number: " << endl;
        string AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "Client is not exist , please try to add a right Account Numebr." << endl;
            AccountNumber = clsInputValidate::ReadString();

        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        Client.Print();

        cout << "Do you want to Update y/n ?" << endl;
        char choise;
        cin >> choise;
        cout << endl;
        if (tolower(choise) == 'n')
        {
            return;
        }
        else
        {
            char changeNew;
            do
            {


                short UpdateCase;
                cout << "Enter which Element you wanna update: " << endl;
                cout << "[1] First Name? " << endl;
                cout << "[2] Last Name? " << endl;
                cout << "[3] Email? " << endl;
                cout << "[4] Phone? " << endl;
                cout << "[5] PinCode? " << endl;
                cout << "[6] Balance? " << endl;
                cout << "[7] All Info? " << endl;
                cin >> UpdateCase;
                cout << "-------------------------------------------------\n";
                switch (UpdateCase)
                {
                case 1:
                {
                    cout << "Enter the new First Name : ";
                    Client.fname = clsInputValidate::ReadString();
                    break;
                }
                case 2:
                {
                    cout << "Enter the new Last Name : ";
                    Client.lname = clsInputValidate::ReadString();
                    break;
                }
                case 3:
                {
                    cout << "Enter the new Email : ";
                    Client.email = clsInputValidate::ReadString();
                    break;
                }
                case 4:
                {
                    cout << "Enter the new Phone : ";
                    Client.phone = clsInputValidate::ReadString();
                    break;
                }
                case 5:
                {
                    cout << "Enter the new PinCode : ";
                    Client.PinCode = clsInputValidate::ReadString();
                    break;
                }
                case 6:
                {
                    cout << "Enter the new Balance : ";
                    Client.AccountBalance = clsInputValidate::ReadDblNumber();
                    break;
                }
                case 7:
                {
                    _ReadClientInfo(Client);
                    break;
                }

                }



                cout << "\nThe new info is: " << endl;
                Client.Print();
                cout << "Do you want to Update again Before Save? y/n" << endl;
                cin >> changeNew;


            } while (tolower(changeNew == 'y'));

        }

        Client.Save();
        cout << "\nSave Done :)" << endl;





    }

};

