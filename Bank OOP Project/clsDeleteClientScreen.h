#pragma once
#include "clsScrean.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"

class clsDeleteClientScreen : protected clsScreen
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


public:
	static void ShowDeleteClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient))
		{
			return;
		}

		string AccountNumber;
		_DrawScreenHeader("\t Delete Client Screen");
		cout << "\nPlease enter your account number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount not Found ,Enter again  :";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintClient(Client);
		cout << "\n Are you sure you want to delete ? ";
		char choice = 'n';
		cin >> choice;
		if (choice == 'Y' || choice == 'y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted Successfully :-)\n";
				_PrintClient(Client);
			}
			else
			{
				cout << "\nError Client Was not Deleted\n";
			}
		}
		
	}
};

