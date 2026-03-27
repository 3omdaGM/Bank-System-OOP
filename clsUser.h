#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsDate.h"
#include "clsUtil.h"


using namespace std;

class clsUser : public clsPerson
{
	//private
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;

	string _UserName;
	string _Password;
	short _Permissions;

	bool _MarkForDelete = 0;

	string _PrepareLogInRecord( string Seperator = "#//#")
	{
		string LoginData = clsDate::GetSystemDateTime() + Seperator +
			UserName + Seperator +
			clsUtil::EncryptText(Password) + Seperator +
			to_string(Permissions);
		return LoginData;

	}

	//-----------------(Find User methods)----------------------

	static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
	{
		vector<string> vUserData;
		vUserData = clsString::Split(Line, Seperator);

		return clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
			vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stod(vUserData[6]));

	}

	struct  stLoginRegisterRecord;

	static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
	{
		 stLoginRegisterRecord vstLoginRegisterRecord;

		vector <string>	vstLoginRegisterLine = clsString::Split(Line, Seperator);

		vstLoginRegisterRecord.DataTime = vstLoginRegisterLine[0];
		vstLoginRegisterRecord.Username = vstLoginRegisterLine[1];
		vstLoginRegisterRecord.Password = vstLoginRegisterLine[2];
		vstLoginRegisterRecord.Permissions = stoi(vstLoginRegisterLine[3]);
		return vstLoginRegisterRecord;
	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	//-----------------(Update User methods)----------------------

	static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
	{
		string Line;
		Line = User.fname + Seperator +
			User.lname + Seperator +
			User.email + Seperator +
			User.phone + Seperator +
			User.UserName + Seperator +
			clsUtil::EncryptText( User.Password )+ Seperator +
			to_string(User.Permissions);
		return Line;
	}

	static vector <clsUser> _LoadUserDataFromFile()
	{
		vector <clsUser> vUsers;
		string DataLine;

		fstream File;
		File.open("Users.txt", ios::in);
		if (File.is_open())
		{
			while (getline(File, DataLine))
			{
				clsUser User = _ConvertLineToUserObject(DataLine);
				vUsers.push_back(User);
			}
			File.close();

		}
		return vUsers;

	}


	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream File;
		File.open("Users.txt", ios::out);
		string DataLine;

		if (File.is_open())
		{
			for (clsUser User : vUsers)
			{
				if (User._MarkForDelete == 0)
				{
					DataLine = _ConvertUserObjectToLine(User);
					File << DataLine << endl;
				}

			}
			File.close();

		}
	}

	void _Update()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUserDataFromFile();
		for (clsUser& User : vUsers)
		{
			if (User.UserName == _UserName)
			{
				User = *this;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);

	}

	//-----------------(Add New User methods)----------------------

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << DataLine << endl;

			MyFile.close();
		}

	}


	//public
public:
	enum enPermissions {
		eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTransactions = 32, pManageUsers = 64,
		pLoginRegister = 128
	};

	struct stLoginRegisterRecord
	{
		string DataTime;
		string Username;
		string Password;
		short Permissions;
	};

	//constructor
	clsUser(enMode Mode, string Fname, string Lname, string Email, string Phone,
		string UserName, string Password, short Permissions) :
		clsPerson(Fname, Lname, Email, Phone)
	{
		_Mode = Mode;
		_UserName = UserName;
		_Password = Password;
		_Permissions = Permissions;

	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	//set UserName
	void setUserName(string UserName)
	{
		_UserName=UserName;
	}

	//get UserName
	string getUserName()
	{
		return _UserName;
	}

	__declspec(property(get = getUserName, put = setUserName)) string UserName;

	//set Password
	void setPassword(string Password)
	{
		_Password = Password;
	}

	//get Password
	string getPassword()
	{
		return _Password;
	}

	__declspec(property(get = getPassword, put = setPassword)) string Password;

	//set Permissions
	void setPermissions(short Permissions)
	{
		_Permissions = Permissions;
	}

	//get Permissions
	short getPermissions()
	{
		return _Permissions;
	}

	__declspec(property(get = getPermissions, put = setPermissions)) short Permissions;

	//print all User data
	void Print()
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << fname;
		cout << "\nLastName    : " << lname;
		cout << "\nFull Name   : " << FullName();
		cout << "\nEmail       : " << email;
		cout << "\nPhone       : " << phone;
		cout << "\nUser Name   : " << _UserName;
		cout << "\nPassword    : " << _Password;
		cout << "\nPermissions : " << _Permissions;
		cout << "\n___________________\n";

	}

	//Find User By Two ways
	//1 -> by User Name only
	//2 -> by User Namer and Password

	// 1) find User by UserName only:

	//-----------------(Find User methods)----------------------

	static clsUser Find(string UserName)
	{
		
		fstream MyFile;
		MyFile.open("Users.txt", ios::in); //read only 

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return  _GetEmptyUserObject();

	}

	// 2) find User by UserName and Password:

	static clsUser Find(string UserName, string Password)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::in); //read only 

		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUserObject(Line);
				if (User.UserName == UserName && User.Password == Password)
				{
					MyFile.close();
					return User;
				}
			}
			MyFile.close();
		}
		return  _GetEmptyUserObject();

	}

	//-----------------(Update User methods)----------------------

	enum enSaveResults { svFailedEmptyObject = 0, svDone = 1, svFailedUserNameExsit = 2 };


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
			if (IsUserExist(_UserName))
			{
				return enSaveResults::svFailedUserNameExsit;
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

	static bool IsUserExist(string UserName)
	{

		clsUser User = clsUser::Find(UserName);

		return (!User.IsEmpty());
	}

	//-----------------(Add New User methods)----------------------

	static clsUser GetObjectForNewUser(string UserName)
	{
		/*return _GetEmptyClientObject();*/
		return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
	}

	//-----------------(Delete User methods)----------------------
	bool Delete()
	{
		vector <clsUser> vUsers;
		vUsers = _LoadUserDataFromFile();

		for (clsUser& User : vUsers)
		{
			if (User.UserName == _UserName)
			{
				User._MarkForDelete = true;
				break;
			}
		}
		_SaveUsersDataToFile(vUsers);
		*this = _GetEmptyUserObject();
		return true;

	}

	//-----------------(Show Users methods)----------------------

	static vector <clsUser> GetUsersList()
	{
		vector <clsUser> vUsers;

		vUsers = _LoadUserDataFromFile();

		return vUsers;
	}

	//-----------------(Permission Users methods)----------------------

	bool CheckAccessPermissions(enPermissions Permissions)
	{
		if (this->Permissions == enPermissions::eAll)
			return true;
		if ((this->Permissions & Permissions) == Permissions)
			return true;
		else
			return false;
		

	}

	//-----------------(Save Users login to file)----------------------

	 void RegisterLogIn()
	{
		 string DataLine = _PrepareLogInRecord();

		 fstream MyFile;
		 MyFile.open("LoginRegister.txt", ios::out | ios::app);

		 if (MyFile.is_open())
		 {

			 MyFile << DataLine << endl;

			 MyFile.close();
		 }
	}


	 //-----------------(Show Users login file)----------------------

	 static vector <stLoginRegisterRecord> GetLoginUsersList()
	 {
		 vector <stLoginRegisterRecord> vLoginRegisterRecord;

		 string DataLine;

		 fstream File;
		 File.open("LoginRegister.txt", ios::in);
		 if (File.is_open())
		 {
			 while (getline(File, DataLine))
			 {
				 stLoginRegisterRecord LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(DataLine);
				 vLoginRegisterRecord.push_back(LoginRegisterRecord);
			 }
			 File.close();

		 }
		 return vLoginRegisterRecord;
		 
	 }
};