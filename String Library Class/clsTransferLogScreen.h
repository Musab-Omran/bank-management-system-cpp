#pragma once

#include <iostream>
#include "clsScreen.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"
#include "GlobalVariables.h"


class clsTransferLogScreen :protected clsScreen
{

private:

    static void PrintTransferLogRecordLine(clsBankClient::stTransferLog TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
        cout << "| " << setw(8) << left << TransferLogRecord.From;
        cout << "| " << setw(8) << left << TransferLogRecord.To;
        cout << "| " << setw(8) << left << TransferLogRecord.AmountTransfered;
        cout << "| " << setw(10) << left << TransferLogRecord.FromBalance;
        cout << "| " << setw(10) << left << TransferLogRecord.ToBalance;
        cout << "| " << setw(8) << left << TransferLogRecord.User;


    }

public:

    static void ShowTransferLogScreen()
    {


        clsBankClient::stTransferLog* vTransferLogRecord = clsBankClient::GetTransferLogData();

        int TransferLogsCount = clsBankClient::TransferLogCount(vTransferLogRecord);
        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(TransferLogsCount) + ") Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
        cout << "| " << left << setw(8) << "s.Acct";
        cout << "| " << left << setw(8) << "d.Acct";
        cout << "| " << left << setw(8) << "Amount";
        cout << "| " << left << setw(10) << "s.Balance";
        cout << "| " << left << setw(10) << "d.Balance";
        cout << "| " << left << setw(8) << "User";

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (TransferLogsCount == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else

            for (int i = 0; i < TransferLogsCount; i++)
            {

                PrintTransferLogRecordLine(vTransferLogRecord[i]);
                cout << endl;
            }

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

