#pragma once
#include "clsScrean.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"

class clsUpdateCurrencyScreen : protected clsScreen
{
	static void _PrintCurrency(clsCurrency& Currency)
	{
		cout << "\nCurrency Card:\n";
		cout << "------------------------------------\n";
		cout << "Country    :" << Currency.Country() << "\n";
		cout << "Code       :" << Currency.CurrencyCode() << "\n";
		cout << "Name       :" << Currency.CurrencyName() << "\n";
		cout << "Rate(1$)   :" << Currency.Rate() << "\n";
		cout << "------------------------------------\n";

	}

	static void _UpdateCurrencyRate(clsCurrency& Currency)
	{
		cout << "\nUpdate Currency Rate:\n";
		cout << "------------------------------------\n";
		cout << "\nEnter New Rate: ";
		float Rate = clsInputValidate::ReadTemplateNumber<float>("Enter Again");
		Currency.UpdateRate(Rate);
		
	}
public:
	static void ShowFindCCurrencyScreen()
	{
		_DrawScreenHeader("\t Find Currency Screen");
		cout << "\nPlease Enter Country Code :";
		string code = "";
		cin>> code;
		clsCurrency Currency = clsCurrency::FindByCode(code);
		if (!Currency.IsEmpty())
		{
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency Was not Found :-(\n";
			return;
		}

		cout << "Are you sue You Want to Update the Rate of This Currency y/n?";
		char ans;
		cin >> ans;
		if (ans == 'Y' || ans == 'y')
		{
			_UpdateCurrencyRate(Currency);
			_PrintCurrency(Currency);
		}
		
	}
};

