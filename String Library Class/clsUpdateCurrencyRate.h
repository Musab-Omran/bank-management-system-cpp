#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "clsFindCurrencyScreen.h"
#include "GlobalVariables.h"

class clsUpdateCurrencyRate : protected clsScreen
{
private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.Country();
        cout << "\nCode       : " << Currency.CurrencyCode();
        cout << "\nName       : " << Currency.CurrencyName();
        cout << "\nRate(1$) = : " << Currency.Rate();

        cout << "\n_____________________________\n";

    }

    static void _ShowResults(clsCurrency Currency)
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

    static clsCurrency _FindCurrency() {
        cout << "\nFind By: [1] Code or [2] Country ? ";
        short Answer = 1;

        cin >> Answer;

        if (Answer == 1)
        {
            string CurrencyCode;
            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
            _ShowResults(Currency);
            return Currency;
        }
        else
        {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);
            return Currency;
        }
    }

public:

	static void ShowUpdateCurrencyRateScreen() {
		clsScreen::_DrawScreenHeader("Update Currency Rate Screen");

        clsCurrency Currency = _FindCurrency();
        
        string answer = clsInputValidate::ReadString("Are you sure you want to update the rate of this currency ? y/n");
        if (answer == "Y" || answer == "y") {
            cout << "Update currency rate : " << endl;
            cout << "enter the new rate to update: ";
            Currency.UpdateRate(clsInputValidate::ReadNumber<float>());
            cout << "Rate Updated Successfully :-)" << endl;
            _PrintCurrency(Currency);
        }
        else {
            cout << "could not update :-(" << endl;
        }
	}
};

