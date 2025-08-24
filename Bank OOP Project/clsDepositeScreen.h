#pragma once
#include "clsScrean.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsDepositeScreen : protected clsScreen
{
	static void _PrintClient(clsBankClient client)
	{
		cout << "\nClient Info:";
		cout << "\n_________________________________________";
		cout << "\nFirst Name     : " << client.FirstName;
		cout << "\nLast Name      : " << client.LastName;
		cout << "\nFull Name      : " << client.FullName();
		cout << "\nEmail          : " << client.Email;
		cout << "\nPhone          : " << client.Phone;
		cout << "\nAccount Number : " << client.AccountNumber;
		cout << "\nPassword       : " << client.PinCode;
		cout << "\nAccount Balance: $" << client.AccountBalance;
		cout << "\n_________________________________________";

	}

	static string _ReadAccountNumber()
	{
		cout << "\nPlease enter your account number: ";
		string AccountNumber = clsInputValidate::ReadString();
		return AccountNumber;
	}

public:
	static void ShowDepositeScreen()
	{
		
		_DrawScreenHeader("\t  Deposit Screen");
		string AccountNumber = _ReadAccountNumber();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient with [" << AccountNumber << "]does Not exist, enter agien\n";
			  AccountNumber = _ReadAccountNumber();

		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		double Amount = 0.0;
		cout << "\n Please Enter deposite Amount :";
		Amount = clsInputValidate::ReadTemplateNumber<double>();

		cout << "\nAre You Sure you want to perform this transaction?";
		char ans = 'n';
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			Client.Deposite(Amount);
			cout << "\nAmount Deposite Successfully.\n";
			cout << "\nNew Balance Is " << Client.AccountBalance;
		}
		else
		{
			cout << "\nOperation Was Cancelled\n";
		}
	
		
	}
};

