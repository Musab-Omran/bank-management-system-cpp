#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsUser.h"
#include "GlobalVariables.h"


class clsLoginRegisterScreen :protected clsScreen
{

private:

    static void PrintLoginRegisterRecordLine(clsUser::LogUser LoginRegisterRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(35) << left << LoginRegisterRecord.Date;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Name;
        cout << "| " << setw(20) << left << LoginRegisterRecord.Password;
        cout << "| " << setw(10) << left << LoginRegisterRecord.Permission;
        cout << "this is the line fo permissions" << LoginRegisterRecord.Permission << endl;
    }

public:

    static void ShowLoginRegisterScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pLoginRegister))
        {
            return;// this will exit the function and it will not continue
        }

        clsUser::LogUser* vLoginRegisterRecord = clsUser::GetRegisterLogData();

        int count = clsUser::LogUserCount(vLoginRegisterRecord);
        string Title = "\tLogin Register List Screen";
        string SubTitle = "\t\t(" + to_string(count) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(35) << "Date/Time";
        cout << "| " << left << setw(20) << "UserName";
        cout << "| " << left << setw(20) << "Password";
        cout << "| " << left << setw(10) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (count == 0)
            cout << "\t\t\t\tNo Logins Available In the System!";
        else

            for (int i = 0; i < count; i++)
            {

                PrintLoginRegisterRecordLine(vLoginRegisterRecord[i]);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

