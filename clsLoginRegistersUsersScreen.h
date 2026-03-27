#pragma once
#include "clsUser.h"
#include "clsScreen.h"
#include <iostream>
#include <iomanip>
#include "clsUser.h"

using namespace std;

class clsLoginRegistersUsersScreen : protected clsScreen
{
private:
    static void _PrintLoginUserRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {

        cout << "| " << setw(15) << left << LoginRegisterRecord.DataTime;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Username;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(12) << left << LoginRegisterRecord.Permissions;

    }
public:



    static void ShowLoginUsersList()
    {
        if (!_CheckPermission(clsUser::enPermissions::pLoginRegister))
        {
            return;
        }

        vector < clsUser::stLoginRegisterRecord> vLoginRegisterRecord = clsUser::GetLoginUsersList();

        string Title = "\tLogin Users List";
        string SubTitle = "\t(" + to_string(vLoginRegisterRecord.size()) + ") Login Users";

        clsScreen::_DrawScreenHeader(Title, SubTitle);

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Date/Time";
        cout << "| " << left << setw(20) << "User Name";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vLoginRegisterRecord.size() == 0)
            cout << "\t\t\t\tNo LoggUsers Available In the System!";
        else

            for (clsUser::stLoginRegisterRecord Record : vLoginRegisterRecord)
            {

                _PrintLoginUserRecordLine(Record);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};



