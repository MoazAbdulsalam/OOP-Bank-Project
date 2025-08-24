#pragma once
#include "clsScrean.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "Global.h"
class clsTransferScreen : protected clsScreen
{
	static void _PrintClient(clsBankClient client)
	{
		cout << "\nClient Card:";
		cout << "\n_________________________________________";
		cout << "\nFull Name      : " << client.FullName();
		cout << "\nAccount Number : " << client.AccountNumber;
		cout << "\nAccount Balance: $" << client.AccountBalance;
		cout << "\n_________________________________________";

	}

	static string _ReadAccountNumber(string Message)
	{

		string AccountNumber;
		cout << Message;
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		return AccountNumber;
	}

public:
	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t Transfer Screen");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("Please Enter AccountNumber To Transfer from "));
		_PrintClient(SourceClient);



		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter AccountNumber To Transfer TO "));
		_PrintClient(DestinationClient);

		if (SourceClient.AccountNumber == DestinationClient.AccountNumber)
		{
		cout << "\nThe 'Source Client' and 'Destination Client' are the same. Transaction Failed !\n";
			return;
		}
	
		cout << "\n Please Enter Transfer Amount :";
		double Amount = clsInputValidate::ReadNumberBetween<double>(1,SourceClient.AccountBalance, "Amount Exceeds The Available Balance, Please Enter Transfer Amount :");


		cout << "\nAre You Sure you want to perform this transaction?";
		char ans = 'n';
		cin >> ans;
		if (ans == 'y' || ans == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.UserName))
			{
				cout << "\nTransfer Done Succefully\n";

				_PrintClient(SourceClient);
				_PrintClient(DestinationClient);
			}
			else
				cout << "\nTransfer Field\n";
		
		}
		else
		{
			cout << "\nOperation Was Cancelled\n";
		}

		

	}
};

