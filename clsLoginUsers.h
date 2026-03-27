#pragma once
#pragma once
#include <iostream>
#include <string>
#include "clsUser.h"
#include "clsString.h"
#include <vector>
#include <fstream>
#include "clsDate.h"

class clsLoginUsers : public clsUser
{
private:
	string _DateTime;

	string _PrepareLogInRecord(string Seperator = "#//#")
	{
		string LoginData = clsDate::GetSystemDateTime() + Seperator +
			UserName + Seperator +
			Password + Seperator +
			to_string(Permissions);
		return LoginData;

	}

};

