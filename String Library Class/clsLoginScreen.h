#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include <iomanip>
#include "clsMainScreen.h"
#include "GlobalUser.h"
#include "GlobalVariables.h"


class clsLoginScreen :protected clsScreen
{

private:

    static  bool _Login()
    {
        bool LoginFaild = false;
        short counter = 3;

        string Username, Password;

        do
        {

            if (LoginFaild)
            {
                cout << "\nInvlaid Username/Password!\n\n";
                cout << "you have " << --counter << " trial(s), try again!" << endl;
            }

            cout << "Enter Username? ";
            cin >> Username;
            cout << "Enter Password? ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFaild = CurrentUser.IsEmpty();

        } while (LoginFaild && counter!=0);

        if (counter != 0) {
           

            CurrentUser._addUserLogin();
            clsMainScreen::ShowMainMenue();

            return true;
        }
        return false;
    }

public:


    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("\t  Login Screen");
        return _Login();

    }

};

