#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;


class clsDeleteUserScreen : protected clsScreen
{
public:

    static void DeleteUser()
    {
        string Title = "\t  Delete User Screen";
        _DrawScreenHeader(Title);

        string UserName = " ";

        cout << "Enter the User Name: ";
        UserName = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nthisUser Name is NOT exist, Please a real one: ";
            UserName = clsInputValidate::ReadString();
        }
        cout << endl;

        clsUser User = clsUser::Find(UserName);
        User.Print();

        char DeleteChoise = ' ';

        cout << "\nAre you want sure that you wanna delete this User? y/n? " << endl;
        cin >> DeleteChoise;

        if (tolower(DeleteChoise) == 'y')
        {
            if (User.Delete())
            {
                cout << "\n\nUser Deleted Successfully :((\n" << endl;
                User.Print();
            }
        }
        else
        {
            cout << "\n\nUser Not Deleted :)" << endl;
        }

    }

};

