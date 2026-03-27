#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalanceScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"


using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:

    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2, eTotalBalance = 3,
        eTransfer = 4, eTransferLog = 5, eMainMenue = 6
    };

    static short _ReadTransactionsOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static  void _GoBackToTransactionMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Transactions Menue...\n";

        system("pause>0");
        ShowTransactionsMenue();
    }

    

    static void _ShowDepositScreen()
    {
        clsDepositScreen::Deposit();
    }

    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::Withdraw();
    }

    static void _ShowTotalBalanceScreen()
    {
        clsTotalBalanceScreen::ShowTotalBalances();
    }

    static void _ShowTransferScreen()
    {
        clsTransferScreen::Transfer();
    }

    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }


   /* static void _ShowTransactionsMainMenueScreen()
    {
        cout << "soon" << endl;
    }*/

    static void _PerfromTransactionsMainMenueOption(enTransactionsMenueOptions TransactionsMainMenueOption)
    {
        switch (TransactionsMainMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            system("cls");            
            _ShowDepositScreen();
            _GoBackToTransactionMenue();
            break;
        }
        case enTransactionsMenueOptions::eWithdraw:
        {
            system("cls");
            _ShowWithdrawScreen();
            _GoBackToTransactionMenue();
            break;
        }

        case enTransactionsMenueOptions::eTotalBalance:
        {
            system("cls");
            _ShowTotalBalanceScreen();
            _GoBackToTransactionMenue();
            break;
        }

        case enTransactionsMenueOptions::eTransfer:
        {
            system("cls");
            _ShowTransferScreen();
            _GoBackToTransactionMenue();
            break;
        }

        case enTransactionsMenueOptions::eTransferLog:
        {
            system("cls");
            _ShowTransferLogScreen();
            _GoBackToTransactionMenue();
            break;
        }

        case enTransactionsMenueOptions::eMainMenue:
        {
         // Let it empty
        }

        }

    }

public:
    static void ShowTransactionsMenue()
    {
        if (!_CheckPermission(clsUser::enPermissions::pTransactions))
        {
            return;
        }
        system("cls");
        _DrawScreenHeader("\tTransaction Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\tTransaction Screen\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer.\n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromTransactionsMainMenueOption((enTransactionsMenueOptions)_ReadTransactionsOption());
    }
};

