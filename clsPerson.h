#pragma once
#include <iostream>
#include <string>
using namespace std;

class clsPerson {

	//private
private:
	string _Fname;
	string _Lname;
	string _Email;
	string _Phone;

	//public
public:

	//constructor
	clsPerson(string fname, string lname, string email, string phone)
	{
		_Fname = fname;
		_Lname = lname;
		_Email = email;
		_Phone = phone;
	}
	//First_Name Set
	void setFname(string fname)
	{
		_Fname = fname;
	}
	//First_Name Get
	string getFname()
	{
		return _Fname;
	}
	__declspec(property(get = getFname, put = setFname)) string fname;

	//Last_Name Set
	void setLname(string lname)
	{
		_Lname = lname;
	}
	//Last_Name Get
	string getLname()
	{
		return _Lname;
	}
	__declspec(property(get = getLname, put = setLname)) string lname;

	//Full Name
	string FullName()
	{
		return fname + " " + lname;
	}

	//Email Set
	void setEmail(string email)
	{
		_Email = email;
	}
	//Email Get
	string getEmail()
	{
		return _Email;
	}
	__declspec(property(get = getEmail, put = setEmail)) string email;

	//Phone Set
	void setPhone(string phone)
	{
		_Phone = phone;
	}
	//Phone Get
	string getPhone()
	{
		return _Phone;
	}
	__declspec(property(get = getPhone, put = setPhone)) string phone;

};