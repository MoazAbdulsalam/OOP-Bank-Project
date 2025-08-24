#pragma once
#include "clsScrean.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsFindClientScreen : protected clsScreen
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
	static void ShowFindClientScrean()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pFindClient))
		{
			return;
		}

		clsScreen::_DrawScreenHeader("\t  Find Client Screen");
		string AccountNumber = "";
		cout << "\n enter Account Number :";
		cin >> AccountNumber;
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\n Not Found Enter Agien:";
			cin >> AccountNumber;
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);
		if (!Client.IsEmpty())
		{
			cout << "\nClient Found :-)\n";
			_PrintClient(Client);
		}
		else
		{
			cout << "\nClient not Found";
		}
	}

};

