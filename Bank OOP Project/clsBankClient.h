#pragma once
#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include "clsPerson.h"
#include "clsString.h" //String library header
#include "clsDate.h"  //Date class header
#include "clsInputValidate.h"


using namespace std;
string ClientsFile = "Clients.txt";

class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarrkedForDelete = false;
	
	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector<string> ClientData = clsString::Split(Line, Seperator);
		clsBankClient NewClient(UpdateMode,ClientData[0], ClientData[1], ClientData[2], ClientData[3], ClientData[4], ClientData[5], stod(ClientData[6]));

		return NewClient;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string Line = Client.FirstName + Seperator + Client.LastName + Seperator + Client.Email + Seperator + Client.Phone + Seperator + Client._AccountNumber + Seperator + Client._PinCode + Seperator + to_string(Client._AccountBalance);
		return Line;
	}

	static void _SaveClientsDataToFile(vector<clsBankClient> Clients)
	{
		fstream MyFile(ClientsFile, ios::out);
		if (MyFile.is_open())
		{
			for (clsBankClient Client : Clients)
			{
				if (Client._MarrkedForDelete) continue; 
				MyFile << _ConvertClientObjectToLine(Client) << endl;
			}
			MyFile.close();
		}
	}

	static vector<clsBankClient> _LoadClientsDataFromFile()
	{
		vector<clsBankClient> _vClients;
		fstream MyFile(ClientsFile, ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				
					_vClients.push_back(Client);
				
			}
			MyFile.close();
		}
		return _vClients;
	}

	void _Update()
	{
		vector<clsBankClient> _vClients = _LoadClientsDataFromFile();
		for(clsBankClient &c : _vClients)
		{
			if(c.AccountNumber == _AccountNumber)
			{
				c = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients);
	}

	void _AddDataLineToFile(string DataLine)
	{
		fstream MyFile(ClientsFile, ios::out |ios::app);
		if(MyFile.is_open())
		{
			MyFile << DataLine << endl;
			MyFile.close();
		}
	
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}
	
	static clsBankClient _GetEmptyClientObjest()
	{
		return clsBankClient(EmptyMode, "", "", "", "", "", "", 0.0f);
	}

	string _PrepareTransferLogRecord( clsBankClient& Destination, float& Amount, string UserName,string Seperator = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber + Seperator;
		TransferLogRecord += Destination.AccountNumber + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(Destination.AccountBalance) + Seperator;
		TransferLogRecord += UserName;
		return TransferLogRecord;
	}


	void _RegisterTransferLog( clsBankClient& Destination, string UserName, float& Amount)
	{
		string Line = _PrepareTransferLogRecord(Destination, Amount, UserName);
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << Line << endl;
			MyFile.close();
		}
	}

	struct stTransferLogComponent;
	static stTransferLogComponent _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLogComponent Record;
		vector<string> Data = clsString::Split(Line,Seperator);
		Record.Date = Data[0];
		Record.SAcct = Data[1];
		Record.DAcct = Data[2];
		Record.Amount =  stof( Data[3]);
		Record.SBalance =stof( Data[4]);
		Record.DBalance =stof( Data[5]);
		Record.UserName = Data[6];
		return Record;
	}

public:

	struct stTransferLogComponent
	{
		string Date;
		string SAcct;
		string DAcct;
		float Amount;
		float SBalance;
		float DBalance;
		string UserName;
	};

	clsBankClient(enMode Mode,string FirstName, string LastName, string Email, string Phone,string AccountNumber,string PinCode,float balance) 
	    : clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = balance;
	}
	
	bool IsEmpty() { return _Mode == EmptyMode; }
	
	//read only properties
	string GetAccountNumber()  { return _AccountNumber; }
	__declspec(property(get = GetAccountNumber)) string AccountNumber;

	void SetPinCode( string PinCode) { _PinCode = PinCode; }
	string GetPinCode() { return _PinCode; }
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float balance) { _AccountBalance = balance; }
	float GetAccountBalance() { return _AccountBalance; }
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;
	



	
	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> clients;
		fstream MyFile(ClientsFile, ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsBankClient client = _ConvertLineToClientObject(Line);
				if (client.AccountNumber == AccountNumber)
				{
					MyFile.close();
					return client;
				}
				clients.push_back(client);
			}
			MyFile.close();
		}
		return _GetEmptyClientObjest();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> Clients;

		fstream File(ClientsFile, ios::in);

		if (File.is_open())
		{
			string Line;
			while (getline(File, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber == AccountNumber && Client.GetPinCode() == PinCode)
				{
					File.close();
					return Client;
				}
				Clients.push_back(Client);
			}
			File.close();
		}


		return _GetEmptyClientObjest();
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		clsBankClient NewClient(AddNewMode, "", "", "", "", AccountNumber, "", 0.0f);
		return NewClient;
	}

	enum enSaveResults { svFaildEmptyObject = 0, svSuccessed = 1 , svFaildAccountNumberExist = 2 };

	enSaveResults Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
		{
			if (IsEmpty())
			{
				return svFaildEmptyObject;
			}
		}
			
		case enMode::UpdateMode:
		{
			_Update();
			return svSuccessed;
		}

		case enMode::AddNewMode :
		{
			if (IsClientExist(_AccountNumber))
			{
				return svFaildAccountNumberExist;
			}
			else
			{
				_AddNew();
				_Mode = UpdateMode; // Change mode to UpdateMode after adding new client
				return svSuccessed;
			}
		}
			
		default:
			break;
		}
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return !Client.IsEmpty();
	}

	static vector<clsBankClient> GetClientsList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient> Clients = GetClientsList();
		double TotalBalance = 0.0;
		for ( clsBankClient& c : Clients)
		{
			TotalBalance += c.AccountBalance;
		}
		return TotalBalance;
	}

	bool Delete()
	{
		vector<clsBankClient> Clients = _LoadClientsDataFromFile();
		for (clsBankClient &c : Clients)
		{
			if (c.AccountNumber == _AccountNumber)
			{
				c._MarrkedForDelete = true;		
				break;
			}
		}
		_SaveClientsDataToFile(Clients);
		*this = _GetEmptyClientObjest(); // Clear the current object after marking for delete
		return true;
	}

	void Deposite(double Amount)
	{
		
		_AccountBalance += Amount;
		Save();
	}

	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
			return 0;

		_AccountBalance -= Amount;
		Save();
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient,string UserName)
	{
		if (Amount > AccountBalance ||( AccountNumber == DestinationClient.AccountNumber))
			return false;
		Withdraw(Amount);
		DestinationClient.Deposite(Amount);
		_RegisterTransferLog(DestinationClient,UserName,Amount);
		return true;
	}
	
	static vector<clsBankClient::stTransferLogComponent> GetTransferLogList()
	{
		vector<clsBankClient::stTransferLogComponent> vTransfer;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			stTransferLogComponent Record;
			while (getline(MyFile, Line))
			{
				Record = _ConvertTransferLogLineToRecord(Line);
				vTransfer.push_back(Record);
			}
			MyFile.close();
		}
		return vTransfer;
	}

};

