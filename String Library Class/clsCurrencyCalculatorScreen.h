#pragma once
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
#include "GlobalVariables.h"

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
	
	static float _ConvertToUSD(clsCurrency currency, float amount) {
		return amount / currency.Rate();
	}

	static float _ConvertToCurrency(clsCurrency CurrencyFrom, clsCurrency CurrencyTo, float amount) {
		return _ConvertToUSD(CurrencyFrom, amount) * CurrencyTo.Rate();
	}

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

	static void ShowCurrencyCalculator() {
		clsScreen::_DrawScreenHeader("Currency Calculator Screen");
        string answer = "n";

        do {
            clsCurrency CurrencyFrom = _FindCurrency();

            clsCurrency CurrencyTo = _FindCurrency();

            cout << "enter the amount to convert: ";
            float amount = clsInputValidate::ReadNumber<float>();

            if (CurrencyTo.CurrencyCode() == "USD") {
                cout << "convert From" << endl;
                _PrintCurrency(CurrencyFrom);
                cout << amount << CurrencyFrom.CurrencyCode() << " = " << _ConvertToUSD(CurrencyFrom, amount) << " USD" << endl;
            }
            else {
                cout << "convert From" << endl;
                _PrintCurrency(CurrencyFrom);
                cout << amount << CurrencyFrom.CurrencyCode() << " = " << _ConvertToUSD(CurrencyFrom, amount) << " USD" << endl;

                cout << "convert To" << endl;
                _PrintCurrency(CurrencyTo);
                cout << amount << CurrencyFrom.CurrencyCode() << " = " << _ConvertToCurrency(CurrencyFrom, CurrencyTo, amount) << CurrencyTo.CurrencyCode() << endl;
            }

            answer = clsInputValidate::ReadString("do you want to perform another calculation? y/n? ");
            system("cls");

        } while (answer == "Y" || answer == "y");
	}
};

