#pragma once
#include "clsScrean.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsFindCurrencyScreen :  protected clsScreen
{
	enum eFindBy{ eCode =1, eCountry =2};

	static void _PrintCurrency(clsCurrency& Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "------------------------------------\n";
		cout << "Country    :" << Currency.Country() << "\n";
		cout << "Code       :" << Currency.CurrencyCode() << "\n";
		cout << "Name       :" << Currency.CurrencyName() << "\n";
		cout << "Rate(1$)   :" << Currency.Rate()<< "\n";
		cout << "------------------------------------\n";

	}

	static void _ShowResults(clsCurrency& Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found :-)\n";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
		}
	}

	static void _FindByCode()
	{
		cout << "\nPlease Enter Currency Code: ";
		string Code = "";
		cin >> Code;
		clsCurrency Currency = clsCurrency::FindByCode(Code);
		_ShowResults(Currency);
	}

	static void _FindByCountry()
	{
		cout << "\nPlease Enter Country Name: ";
		string Country = "";
		cin >> Country;
		clsCurrency Currency = clsCurrency::FindByCountry(Country);
		_ShowResults(Currency);

	}

	static void _PerformChoice(eFindBy op)
	{
		switch (op)
		{
		case clsFindCurrencyScreen::eCode:
			_FindByCode();
			break;
		case clsFindCurrencyScreen::eCountry:
			_FindByCountry();
			break;
		}
	}
public:
	static void ShowFindCCurrencyScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");
		cout << "\nFind By [1] Code or [2] Country :";
		short Choice = clsInputValidate::ReadNumberBetween<short>(1, 2, "Enter 1 or 2? ");
		_PerformChoice((eFindBy)Choice);
	}
};

