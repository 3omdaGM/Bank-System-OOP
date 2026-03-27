#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsUpdateUserScreen : clsScreen
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


    static void UpdateUser()

    {
        string Title = "\t  Update User Screen";
        _DrawScreenHeader(Title);

        cout << "Enter User Name: ";;
        string UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser is not exist , please try to add a right User Name ---> ";
            UserName = clsInputValidate::ReadString();

        }
        cout << endl;

        clsUser User = clsUser::Find(UserName);
        User.Print();

        cout << "Do you want to Update y/n ? ";;
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
                cout << "[5] Password? " << endl;
                cout << "[6] Permissons? " << endl;
                cout << "[7] All Info? " << endl;
                UpdateCase = clsInputValidate::ReadShortNumberBetween(1, 7);
                cout << "-------------------------------------------------\n";
                switch (UpdateCase)
                {
                case 1:
                {
                    cout << "Enter the new First Name : ";
                    User.fname = clsInputValidate::ReadString();
                    break;
                }
                case 2:
                {
                    cout << "Enter the new Last Name : ";
                    User.lname = clsInputValidate::ReadString();
                    break;
                }
                case 3:
                {
                    cout << "Enter the new Email : ";
                    User.email = clsInputValidate::ReadString();
                    break;
                }
                case 4:
                {
                    cout << "Enter the new Phone : ";
                    User.phone = clsInputValidate::ReadString();
                    break;
                }
                case 5:
                {
                    cout << "Enter the new Password : ";
                    User.Password = clsInputValidate::ReadString();
                    break;
                }
                case 6:
                {
                    cout << "Enter the new Permissions : ";
                    User.Permissions = _ReadPermissions();
                    break;
                }
                case 7:
                {
                    _ReadUserInfo(User);
                    break;
                }

                }



                cout << "\nThe new User's info is: " << endl;
                User.Print();
                cout << "Do you want to Update again Before Save? y/n? ";
                cin >> changeNew;


            } while (tolower(changeNew == 'y'));

        }

        User.Save();
        cout << "\nSave Done :)" << endl;


    }

};

