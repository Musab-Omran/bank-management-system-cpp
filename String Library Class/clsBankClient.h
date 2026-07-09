#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include "clsDate.h"
#include "GlobalUser.h"
#include "GlobalVariables.h"


using namespace std;
class clsBankClient : public clsPerson
{

public:

    clsBankClient() {
        AccountBalance = -1;
    }

    static int Size;

    struct stTransferLog {
        string DateTime, From, To, User;
        double AmountTransfered = -1, FromBalance, ToBalance;
    };


private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkedForDelete = false;

    static clsBankClient _ConvertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        string* vClientData;
        int size = 0;
        vClientData = clsString::Split(Line, Seperator, size);

        clsBankClient x = clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));

        delete[] vClientData;
        return x;
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName + Seperator;
        stClientRecord += Client.LastName + Seperator;
        stClientRecord += Client.Email + Seperator;
        stClientRecord += Client.Phone + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode + Seperator;
        stClientRecord += to_string(Client.AccountBalance);

        return stClientRecord;

    }

    static clsBankClient* _LoadClientsDataFromFile()
    {

        clsBankClient* vClients = new clsBankClient[MaxNumberOfClients];

        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            int i = 0;

            while (getline(MyFile, Line))
            {
                if (i >= MaxNumberOfClients)
                    break;

                clsBankClient Client = _ConvertLinetoClientObject(Line);

                vClients[i] = (Client);
                i++;
            }

            MyFile.close();

            Size = i;

        }


        return vClients;

    }

    static void _SaveCleintsDataToFile(clsBankClient* vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (int i = 0; i < Size; i++)
            {
                if (vClients[i].MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverClientObjectToLine(vClients[i]);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        clsBankClient* _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (int i = 0; i < Size; i++)
        {
            if (_vClients[i].AccountNumber() == AccountNumber())
            {
                _vClients[i] = *this;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);
        delete[] _vClients;
    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverClientObjectToLine(*this));
        Size++;
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    string _currentTransferLogLine(clsBankClient To, double Amount, string seperator = "#//#") {

        string line = clsDate::GetSystemDateTimeString() + seperator;
        line += _AccountNumber + seperator;
        line += To.AccountNumber() + seperator;
        line += to_string(Amount) + seperator;
        line += to_string(_AccountBalance) + seperator;
        line += to_string(To.AccountBalance) + seperator;
        line += CurrentUser.UserName;

        return line;
    }

    void _AddTranferLog(clsBankClient To, double Amount, string seperator = "#//#") {

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << _currentTransferLogLine(To, Amount) << endl;
            MyFile.close();
        }
    }

    static stTransferLog _convertLineToTransferLogStructure(string line, string Seperator = "#//#") {
        stTransferLog vLogs;
        int size = 0;
        string* data = clsString::Split(line, Seperator, size);
        vLogs.DateTime = data[0];
        vLogs.From = data[1];
        vLogs.To = data[2];
        vLogs.AmountTransfered = stod(data[3]);
        vLogs.FromBalance = stod(data[4]);
        vLogs.ToBalance = stod(data[5]);
        vLogs.User = data[6];
        
        delete[] data;

        return vLogs;
    }

    static stTransferLog* _loadTransferLogFromfile() {

        stTransferLog* vLogUsers = new stTransferLog[NumberOfTransferLogs];

        fstream MyFile;
        MyFile.open("TransferLog.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            int i = 0;
            while (getline(MyFile, Line))
            {

                stTransferLog Logs = _convertLineToTransferLogStructure(Line);

                vLogUsers[i] = (Logs);
            }

            MyFile.close();

        }

        return vLogUsers;
    }

public:


    clsBankClient(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string AccountNumber, string PinCode,
        float AccountBalance) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    static clsBankClient Find(string AccountNumber)
    {


        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {



        fstream MyFile;
        MyFile.open("Clients.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLinetoClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyClientObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {

                return enSaveResults::svFaildEmptyObject;

            }

        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsBankClient::IsClientExist(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }



    }

    static bool IsClientExist(string AccountNumber)
    {

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        return (!Client1.IsEmpty());
    }

    bool Delete()
    {
        clsBankClient* _vClients;
        _vClients = _LoadClientsDataFromFile();

        for (int i = 0; i < Size; i++)
        {
            if (_vClients[i].AccountNumber() == _AccountNumber)
            {
                _vClients[i]._MarkedForDelete = true;
                break;
            }

        }

        _SaveCleintsDataToFile(_vClients);
        Size--;

        *this = _GetEmptyClientObject();

        delete[] _vClients;

        return true;

    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    static clsBankClient* GetClientsList()
    {
        return _LoadClientsDataFromFile();
    }


    void Deposit(double Amount)
    {
        _AccountBalance += Amount;
        save();
    }

    bool Withdraw(double Amount)
    {
        if (_AccountBalance < Amount) {
            return false;
        }
        else {
            _AccountBalance -= Amount;
            save();
        }
    }

    static double GetTotalBalances()
    {
        clsBankClient* vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;

        for (int i = 0; i < Size; i++)
        {

            TotalBalances += vClients[i].AccountBalance;
        }

        return TotalBalances;
    }

    bool Transfer(float Amount, clsBankClient& DestinationClient)
    {
        if (Amount > AccountBalance)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _AddTranferLog(DestinationClient, Amount);
        return true;
    }

    static stTransferLog* GetTransferLogData() {
        return _loadTransferLogFromfile();
    }

    static int TransferLogCount(stTransferLog* arr) {

        int i;
        for (i = 0; i < NumberOfTransferLogs; i++) {
            if (arr[i].AmountTransfered == -1) {
                break;
            }
        }
        return i;
    }

};

