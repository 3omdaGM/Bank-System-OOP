#pragma once
#include "clsBankClient.h"
#include "clsScreen.h"
#include <iostream>
#include <iomanip>

using namespace std;

class clsClientsListScreen : protected clsScreen
{
private:
   static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.phone;
        cout << "| " << setw(20) << left << Client.email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }
public:
    
  

  static   void ShowClientsList()
    {

      if (!_CheckPermission(clsUser::enPermissions::pListClients))
      {
          return;
      }

        vector <clsBankClient> vClients = clsBankClient::GetClientsList();

        string Title = "\t\tClients List";
        string SubTitle = "\t\t(" + to_string(vClients.size()) + ") Clients";

        clsScreen::_DrawScreenHeader(Title,SubTitle);

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {

                _PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

