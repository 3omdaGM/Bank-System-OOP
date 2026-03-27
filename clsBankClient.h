#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>

using namespace std;

class clsBankClient : public clsPerson
{
	//private
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkForDelete = 0;

	//-----------------(Find Client methods)----------------------

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> vClientData;
		vClientData = clsString::Split(Line, Seperator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	struct stTrnsferLogRecord;

	static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTrnsferLogRecord TrnsferLogRecord;

		vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
		TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
		TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
		TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
		TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
		TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
		TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
		TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

		return TrnsferLogRecord;

	}

	//-----------------(Update Client methods)----------------------

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string Line;
		Line = Client.fname + Seperator +
			Client.lname + Seperator +
			Client.email + Seperator +
			Client.phone + Seperator +
			Client.AccountNumber() + Seperator +
			Client.PinCode + Seperator +
			to_string(Client.AccountBalance);
		return Line;
	}

	static vector <clsBankClient> _LoadClientDataFromFile()
	{
		vector <clsBankClient> vClients;
		string DataLine;

		fstream File;
		File.open("Clients.txt", ios::in);
		if (File.is_open())
		{
			while (getline(File, DataLine))
			{
				clsBankClient Client = _ConvertLineToClientObject(DataLine);
				vClients.push_back(Client);
			}
			File.close();

		}
		return vClients;

	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream File;
		File.open("Clients.txt", ios::out);
		string DataLine;

		if (File.is_open())
		{
			for (clsBankClient C : vClients)
			{
				if (C._MarkForDelete == 0)
				{
					DataLine = _ConvertClientObjectToLine(C);
					File << DataLine << endl;
				}

			}
			File.close();

		}
	}

	void _Update()
	{
		vector <clsBankClient> vClients;
		vClients = _LoadClientDataFromFile();
		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);

	}

	//-----------------(Add New CLient methods)----------------------

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));

		/*
		vector <clsBankClient> vClients;
		vClients = _LoadClientDataFromFile();
		vClients.push_back(*this);
		_SaveClientsDataToFile(vClients);
		*/
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << DataLine << endl;

			MyFile.close();
		}

	}

	//-----------------(Transfer Client methods)----------------------

	string _PrepareTransferLogRecord(float Amount, clsBankClient DestinationClient,
		string UserName, string Seperator = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTime() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;
		return TransferLogRecord;
	}

	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient, string UserName)
	{

		string stDataLine = _PrepareTransferLogRecord(Amount, DestinationClient, UserName);

		fstream MyFile;
		MyFile.open("TransfersLog.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}


	//public
public:

	struct stTrnsferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float Amount;
		float srcBalanceAfter;
		float destBalanceAfter;
		string UserName;

	};


	//constructor
	clsBankClient(enMode Mode, string Fname, string Lname, string Email, string Phone,
		string AccountNumber, string PinCode, float AccountBalance) :
		clsPerson(Fname, Lname, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;

	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	//return AccountNumber
	string AccountNumber()
	{
		return _AccountNumber;
	}

	//set PinCode
	void setPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}

	//get PinCode
	string getPinCode()
	{
		return _PinCode;
	}

	__declspec(property(get = getPinCode, put = setPinCode)) string PinCode;

	//set AccountBalance
	void setAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}

	//get AccountBalance
	float getAccountBalance()
	{
		return _AccountBalance;
	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance)) float AccountBalance;

	//print all client data
	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << fname;
		cout << "\nLastName    : " << lname;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << email;
		cout << "\nPhone       : " << phone;
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPinCode     : " << _PinCode;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}

	void MiniPrint()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFull Name   : " << FullName();
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nBalance     : " << _AccountBalance;
		cout << "\n___________________\n";

	}

	//Find Client By Two ways
	//1 -> by AccountNumber only
	//2 -> by AccountNumbe and PinCode

	// 1) find client by AccountNumber only:

	//-----------------(Find Client methods)----------------------

	static clsBankClient Find(string AccountNumber)
	{
		/*vector <clsBankClient> vClients;*/
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); //read only 

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				/*vClients.push_back(Client);*/
			}
			MyFile.close();
		}
		return  _GetEmptyClientObject();

	}

	// 2) find client by AccountNumber and PinCode:

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		/*vector <clsBankClient> vClients;*/
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in); //read only 

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				/*vClients.push_back(Client);*/
			}
			MyFile.close();
		}
		return  _GetEmptyClientObject();

	}

	//-----------------(Update Client methods)----------------------

	enum enSaveResults { svFailedEmptyObject = 0, svDone = 1, svFailedAccountNumberExsit = 2 };

	/*enum enAddResult { addFaild = 0, addDone = 1 };*/

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			return  enSaveResults::svFailedEmptyObject;
		}
		case enMode::UpdateMode:
		{
			_Update();
			return  enSaveResults::svDone;
		}

		case enMode::AddNewMode:
		{
			if (IsClientExist(_AccountNumber))
			{
				return enSaveResults::svFailedAccountNumberExsit;
			}
			else
			{
				_AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResults::svDone;
			}

		}
		}
	}

	static bool IsClientExist(string AccountNumber)
	{

		clsBankClient Client1 = clsBankClient::Find(AccountNumber);

		return (!Client1.IsEmpty());
	}

	//-----------------(Add New Client methods)----------------------

	static clsBankClient GetObjectForNewClient(string AccountNumber)
	{
		/*return _GetEmptyClientObject();*/
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	//-----------------(Delete Client methods)----------------------
	bool Delete()
	{
		vector <clsBankClient> vClients;
		vClients = _LoadClientDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = 1;
				break;
			}
		}
		_SaveClientsDataToFile(vClients);
		*this = _GetEmptyClientObject();
		return true;

	}

	//-----------------(Show Clients methods)----------------------

	static vector <clsBankClient> GetClientsList()
	{
		vector <clsBankClient> vClients;

		vClients = _LoadClientDataFromFile();

		return vClients;
	}

	static double GetTotalBalances()
	{
		double TotalBalance = 0;
		vector <clsBankClient> vClients;

		vClients = _LoadClientDataFromFile();

		for (clsBankClient& Client : vClients)
		{
			TotalBalance += Client.AccountBalance;
		}
		return TotalBalance;

	}

	//-----------------(Deposit method)----------------------

	void Deposit(double DepositAmount)
	{
		_AccountBalance += DepositAmount;
		Save();
	}

	//-----------------(Withdraw method)----------------------

	bool Withdraw(double WithdrawAmount)
	{
		if (WithdrawAmount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= WithdrawAmount;
			Save();
		}
		
	}

	//-----------------(Transfer method)----------------------
	bool Transfer(clsBankClient& DistinationClient , float Amount, string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}
		Withdraw(Amount);
		DistinationClient.Deposit(Amount);	
		_RegisterTransferLog(Amount, DistinationClient, UserName);

		return true;

	}

	static  vector <stTrnsferLogRecord> GetTransfersLogList()
	{
		vector <stTrnsferLogRecord> vTransferLogRecord;

		fstream MyFile;
		MyFile.open("TransfersLog.txt", ios::in);//read Mode

		if (MyFile.is_open())
		{

			string Line;

			stTrnsferLogRecord TransferRecord;

			while (getline(MyFile, Line))
			{

				TransferRecord = _ConvertTransferLogLineToRecord(Line);

				vTransferLogRecord.push_back(TransferRecord);

			}

			MyFile.close();

		}

		return vTransferLogRecord;

	}


};