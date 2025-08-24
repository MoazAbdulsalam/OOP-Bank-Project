#pragma once
#include "clsScrean.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
class clsAddNewClientScreen :  protected clsScreen
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

	static void ShowAddNewClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pAddNewClient))
		{
			return;
		}

		_DrawScreenHeader("\t Add New Client Screen");
		string AccountNumber = "";

		cout << "\nPlease Enter Account Number: ";
		AccountNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount Number Is Already Used, Choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}

		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);


		_ReadClientInfo(NewClient);

		clsBankClient::enSaveResults SaveResult;

		SaveResult = NewClient.Save();

		switch (SaveResult)
		{
		    case  clsBankClient::enSaveResults::svSuccessed:
		    {
		    	cout << "\nAccount Addeded Successfully :-)\n";
		    	_PrintClient(NewClient);
		    	break;
		    }
		    case clsBankClient::enSaveResults::svFaildEmptyObject:
		    {
		    	cout << "\nError account was not saved because it's Empty";
		    	break;
		    
		    }
		    case clsBankClient::enSaveResults::svFaildAccountNumberExist:
		    {
		    	cout << "\nError account was not saved because account number is used!\n";
		    	break;
		    
		    }
		}
	}

};

