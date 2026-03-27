#pragma once
#include <iostream>
#include "clsUser.h"
#include "Global.h"
#include "clsDate.h"


using namespace std;

class clsScreen
{
protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {
        cout << "\t\t\t\t\t______________________________________________";
        cout << "\n\n\t\t\t\t\t   " << Title;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t  " << SubTitle;
        }
        cout << "\n\t\t\t\t\t______________________________________________\n\n";

        cout << "\t\t\t\t\t\t User:   " << CurrentUser.fname;
        cout << "\n\t\t\t\t\t\t Date:  " << clsDate::GetSystemDate().DateToString() << endl;;
        cout << "\n\t\t\t\t\t______________________________________________\n\n";

    }

    static bool _CheckPermission(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermissions(Permission))
        {
            /*cout<< "\nDon't Have the access to this page :( !\n";*/
            _DrawScreenHeader("Don't Have the access to this page :( !");
            return false;
        }
        else
        {
            return true;
        }
    }


};

