#pragma once
#include "clsScrean.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include"clsUpdateCurrencyScreen.h"
#include "clsCurrencyCalculaterScreen.h"
class clsShowCurrencyExchangeScreen : protected clsScreen
{
	enum enCurrencyExchangeMenue
	{
		elistCurrencies=1
		,eFindCurrency=2
		,eUpdateCurrency=3
		,eCurrencyCalculater=4
		,eMainMinue=5
	};

	static short _ReadMenueOption()
	{
		cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 5, "Enter Number between 1 to 8? ");
		return Choice;
	}

	static  void _GoBackToCurrencyMenue()
	{
		cout << "\nPress any key to go back to Currency Menue...\n";

		system("pause>0");
		ShowShowCurrencyExchangeScreen();
	}

	static void _ShowListCurrenciesScreen()
	{
		clsCurrenciesListScreen::ShowListCurrenciesScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrencyScreen::ShowFindCCurrencyScreen();
	}
	static void _ShowUpdateCurrencyScreen()
	{
		clsUpdateCurrencyScreen::ShowFindCCurrencyScreen();
	}
	static void _ShowCurrencyCalculaterScreen()
	{
		clsCurrencyCalculaterScreen::ShowCurrencyCalculatorScreen();
	}
	
	static void _PerformCurrencyMenueOption(enCurrencyExchangeMenue op)
	{
		switch (op)
		{
		case clsShowCurrencyExchangeScreen::elistCurrencies:
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyMenue();
			break;
		case clsShowCurrencyExchangeScreen::eFindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyMenue();
			break;
		case clsShowCurrencyExchangeScreen::eUpdateCurrency:
			system("cls");
			_ShowUpdateCurrencyScreen();
			_GoBackToCurrencyMenue();
			break;
		case clsShowCurrencyExchangeScreen::eCurrencyCalculater:
			system("cls");
			_ShowCurrencyCalculaterScreen();
			_GoBackToCurrencyMenue();
			break;
		case clsShowCurrencyExchangeScreen::eMainMinue:

			break;
		
		}
	}
public:
	static void ShowShowCurrencyExchangeScreen()
	{
		system("cls");
		_DrawScreenHeader("\t\Currency Exchange Menue");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
		cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
		cout << setw(37) << left << "" << "\t[3] Update Currency.\n";
		cout << setw(37) << left << "" << "\t[4] Currency Calculater.\n";
		cout << setw(37) << left << "" << "\t[5] Main Minue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformCurrencyMenueOption((enCurrencyExchangeMenue)_ReadMenueOption());
	}
};

