#pragma once
#include "clsScrean.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsUpdateClientScreen :   protected clsScreen
{
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "Please enter your first name: ";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "Please enter your last name: ";
		Client.LastName = clsInputValidate::ReadString();
		cout << "Please enter your email: ";
		Client.Email = clsInputValidate::ReadString();
		cout << "Please enter your phone number: ";
		Client.Phone = clsInputValidate::ReadString();
		cout << "Please enter your Pin Code: ";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "Please enter your account balance: ";
		Client.AccountBalance = clsInputValidate::ReadTemplateNumber<float>("Invalid input. Please enter a valid account balance: ");


	}

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

	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
		{
			return;
		}

		_DrawScreenHeader("\t Update Client Screen");
		string AccountNumber = "";

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		cout << "Are You Sure You Want To Update ?";
		char ans = 'n';
		cin >> ans;
		if (ans == 'Y' || ans == 'y')
		{
			cout << "\n\n Update Client Info:";
			cout << "\n----------------------\n";

			_ReadClientInfo(Client);


			clsBankClient::enSaveResults SaveResult;

			SaveResult = Client.Save();

			switch (SaveResult)
			{
			    case  clsBankClient::enSaveResults::svSuccessed:
			    {
			    	cout << "\nAccount Updated Successfully :-)\n";
			    
			    	_PrintClient(Client);
			    	break;
			    }
			    case clsBankClient::enSaveResults::svFaildEmptyObject:
			    {
			    	cout << "\nError account was not saved because it's Empty";
			    	break;
			    
			    }

			}
		}
	}
};

