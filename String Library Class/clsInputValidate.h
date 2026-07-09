#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"
#include "GlobalVariables.h"
#include <regex>

using namespace std;

class clsInputValidate
{

public:

	template <typename T> static bool IsNumberBetween(T Number, T From, T To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	template <typename T> static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		T Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	template <typename T> static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		T Number = ReadNumber<int>();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber<int>();
		}
		return Number;
	}

	static string ReadStringContainNumber(string msg = "") {
		string s1;
		cout << msg << endl;
		getline(cin >> ws, s1);
		return s1;
	}




	static string ReadString(string msg = "") {
		string s1;
		regex emailPattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
		regex numberPattern(R"(^\d+$)");

		while (true) {
			cout << msg << endl;
			getline(cin >> ws, s1);

			if (regex_match(s1, numberPattern) || regex_match(s1, emailPattern)) {
				return s1; // Valid: all digits or valid email
			}

			// Check if string contains any digit
			if (s1.find_first_of("0123456789") == string::npos) {
				return s1; // Valid: no digits at all
			}

			cout << "Invalid input. Numbers are only allowed in emails or if the entire input is a number.\n";
		}
	}

};

