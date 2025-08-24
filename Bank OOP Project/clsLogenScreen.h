#pragma once
#include "clsScrean.h"
#include<fstream>
#include"clsUser.h"
#include "clsMainScreen.h"
#include"Global.h"
#include"clsDate.h"

class clsLoginScreen : protected clsScreen
{
	static bool _Login()
	{
		short count = 3;
		bool LoginFaild = false;
		string UserName, Password;
		do
		{
			if (LoginFaild)
			{
				count--;
				cout << "\nWrong UserName/Password!\n";
				cout << "you have " << count << " Trials To login.\n\n";
				if (count == 0)
				{
					cout << "\n\t\t\t \t\t\tSystem Locked!!!!!!\n\n";
					return false;
				}
			}
			cout << "Enter UserName?";
			cin >> UserName;
			cout << " Enter Password?";
			cin >> Password;
		    CurrentUser = clsUser::Find(UserName, Password);
			
			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);
		CurrentUser.RegisterLogIn();
		clsMainScreen::ShowMainMenue();
		return true;
	}
	



public:
	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();
	}
};

