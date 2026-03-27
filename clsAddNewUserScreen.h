#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
{
private:

    static short _ReadPermissions()
    {
        char PerChoise;
        cout << "\n\nDo you want to give Full access? y/n? ";
        cin >> PerChoise;
        
        if (tolower(PerChoise) == 'y')
        {
            return clsUser::enPermissions::eAll;
        }
        else
        {

            short TotalPermissions = 0;
            cout << "\nDo you want to give access to : \n";

            cout << "\n\nShow Clients List? y/n? ";
            cin >> PerChoise;
            if (tolower(PerChoise) == 'y')
            {
                TotalPermissions += clsUser::enPermissions::pListClients;
            }

            cout << "\nAdd New Client? y/n? ";
            cin >> PerChoise;
            if (tolower(PerChoise) == 'y')
            {
                TotalPermissions += clsUser::enPermissions::pAddNewClient;
            }

            cout << "\nDelete Client? y/n? ";
            cin >> PerChoise;
            if (tolower(PerChoise) == 'y')
            {
                TotalPermissions += clsUser::enPermissions::pDeleteClient;
            }

            cout << "\nUpdate Client? y/n? ";
            cin >> PerChoise;
            if (tolower(PerChoise) == 'y')
            {
                TotalPermissions += clsUser::enPermissions::pUpdateClients;
            }

            cout << "\nFind Client? y/n? ";
            cin >> PerChoise;
            if (tolower(PerChoise) == 'y')
            {
                TotalPermissions += clsUser::enPermissions::pFindClient;
            }

            cout << "\nTransactions? y/n? ";
            cin >> PerChoise;
            if (tolower(PerChoise) == 'y')
            {
                TotalPermissions += clsUser::enPermissions::pTransactions;
            }

            cout << "\nManage Users? y/n? ";
            cin >> PerChoise;
            if (tolower(PerChoise) == 'y')
            {
                TotalPermissions += clsUser::enPermissions::pManageUsers;
            }

            cout << "\nLogin Register? y/n? ";
            cin >> PerChoise;
            if (tolower(PerChoise) == 'y')
            {
                TotalPermissions += clsUser::enPermissions::pLoginRegister;
            }

            return TotalPermissions;


        }
    }

    static void _ReadUserInfo(clsUser& User)
    {

        cout << "\nEnter the First Name  : ";
        User.fname = clsInputValidate::ReadString();

        cout << "\nEnter the Last Name   : ";
        User.lname = clsInputValidate::ReadString();

        cout << "\nEnter the Email       : ";
        User.email = clsInputValidate::ReadString();

        cout << "\nEnter the Phone       : ";
        User.phone = clsInputValidate::ReadString();

        cout << "\nEnter the Password    : ";
        User.Password = clsInputValidate::ReadString();

        cout << "\nEnter the Permissions : ";
        User.Permissions = _ReadPermissions();

    }

public:

    static  void AddNewUser()
    {
        string Title = "\t  Add New User Screen";
        _DrawScreenHeader(Title);

        string UserName = " ";

        cout << "Enter the User Name: ";
        UserName = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(UserName))
        {
            cout << "\nError! This User Name is already Exist, Please choose another one: ";
            UserName = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::GetObjectForNewUser(UserName);
        _ReadUserInfo(User);

        clsUser::enSaveResults SaveResult;
        SaveResult = User.Save();

        switch (SaveResult)
        {
        case clsUser::enSaveResults::svDone:
        {
            cout << "\nUser Added Successfully :)" << endl;
            break;
        }
        case clsUser::enSaveResults::svFailedEmptyObject:
        {
            cout << "\nError! User was not saved because it's Empty";
            break;

        }
        case clsUser::enSaveResults::svFailedUserNameExsit:
        {
            cout << "\nError! User was not saved because this User Name is already used!\n";
            break;
        }
        }

    }

};


