#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:

    static void _ReadClientInfo(clsBankClient& Client)
    {

        cout << "Enter the First Name : ";
        Client.fname = clsInputValidate::ReadString();

        cout << "Enter the Last Name  : ";
        Client.lname = clsInputValidate::ReadString();

        cout << "Enter the Email      : ";
        Client.email = clsInputValidate::ReadString();

        cout << "Enter the Phone      : ";
        Client.phone = clsInputValidate::ReadString();

        cout << "Enter the PinCode    : ";
        Client.PinCode = clsInputValidate::ReadString();

        cout << "Enter the Balance    : ";
        Client.AccountBalance = clsInputValidate::ReadDblNumber();

    }

public:

   static  void AddNewClient()
    {
       if (!_CheckPermission(clsUser::enPermissions::pAddNewClient))
       {
           return;
       }
       string Title = "\t  Add New Client Screen";
       _DrawScreenHeader(Title);

        string AccountNumber = " ";

        cout << "Enter the Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nthis Account Number is already Exist, Please choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::GetObjectForNewClient(AccountNumber);
        //Client.AccountNumber() = AccountNumber;
        _ReadClientInfo(Client);

        clsBankClient::enSaveResults SaveResult;
        SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svDone:
        {
            cout << "\nClient Added Successfully :)" << endl;
            break;
        }
        case clsBankClient::enSaveResults::svFailedEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty";
            break;

        }
        case clsBankClient::enSaveResults::svFailedAccountNumberExsit:
        {
            cout << "\nError account was not saved because account number is used!\n";
            break;
        }
        }

    }


};

