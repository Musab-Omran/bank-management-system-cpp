#pragma once
#include <iostream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include <fstream>
#include "clsDate.h"
#include "clsUtil.h"
#include "GlobalVariables.h"

using namespace std;
class clsUser : public clsPerson
{
    public:
        struct LogUser {
            string Date, Name, Password, Permission;
        };

        static int Size;

    private:

        enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
        enMode _Mode;
        string _UserName;
        string _Password;
        int _Permissions;

        bool _MarkedForDelete = false;

        clsUser() {

        }
    



    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        string* vUserData;
        int size = 0;
        vUserData = clsString::Split(Line, Seperator, size);

        clsUser x= clsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
            vUserData[3], vUserData[4], clsUtil::DecryptText(vUserData[5]), stoi(vUserData[6]));
        
        delete[] vUserData;

        return x;
    }

    string _currentUserLogLine(string seperator = "#//#") {
        string line = clsDate::GetSystemDateTimeString() + seperator;
        line += _UserName + seperator;
        line += clsUtil::EncryptText(_Password) + seperator;
        line += to_string(_Permissions);
        return line;
    }

    static LogUser _convertLineToUserLogStructure(string line, string Seperator="#//#") {
        LogUser vLogUsers;
        int size = 0;
        string* data = clsString::Split(line, Seperator, size);
        vLogUsers.Date = data[0];
        vLogUsers.Name = data[1];
        vLogUsers.Password = clsUtil::DecryptText(data[2]);
        vLogUsers.Permission = data[3];
        delete[] data;
        return vLogUsers;
    }

    static LogUser* _loadLogUsersFromfile(){

        LogUser* vLogUsers = new LogUser[MaxNumberOfLoginsUser];

        fstream MyFile;
        MyFile.open("LogRejesters.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            int i = 0;
            while (getline(MyFile, Line))
            {
                if (i >= MaxNumberOfLoginsUser)
                    break;

                LogUser User = _convertLineToUserLogStructure(Line);

                vLogUsers[i] = (User);
                i++;
            }
            Size = i;

            MyFile.close();

        }

        return vLogUsers;
    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.FirstName + Seperator;
        UserRecord += User.LastName + Seperator;
        UserRecord += User.Email + Seperator;
        UserRecord += User.Phone + Seperator;
        UserRecord += User.UserName + Seperator;
        UserRecord += clsUtil::EncryptText(User.Password) + Seperator;
        UserRecord += to_string(User.Permissions);

        return UserRecord;

    }

    static  clsUser* _LoadUsersDataFromFile()
    {

        clsUser* vUsers = new clsUser[MaxNumberOfUsers];

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;
            int i = 0;

            while (getline(MyFile, Line))
            {
                if (i >= MaxNumberOfUsers)
                    break;

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers[i] = (User);
                i++;
            }
            Size = i;
            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(clsUser* vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (int i = 0; i < Size; i++)
            {
                if (vUsers[i].MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(vUsers[i]);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        clsUser* _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (int i = 0; i < Size; i++)
        {
            if (_vUsers[i].UserName == UserName)
            {
                _vUsers[i] = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);
        delete[] _vUsers;
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConverUserObjectToLine(*this));
        Size++;
    }

    void _AddDataLineToFile(string  stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pLoginRegister = 64, pManageUsers = 128
    };

    

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkedForDelete;
    }

    string GetUserName()
    {
        return _UserName;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;

    static clsUser Find(string UserName)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLinetoUserObject(Line);
                if (User.UserName == UserName && User.Password == Password)
                {
                    MyFile.close();
                    return User;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildUserExists = 2 };

    enSaveResults Save()
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
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResults::svFaildUserExists;
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

    static bool IsUserExist(string UserName)
    {

        clsUser User = clsUser::Find(UserName);
        return (!User.IsEmpty());
    }

    bool Delete()
    {
        clsUser* vUsers;
        vUsers = _LoadUsersDataFromFile();

        for (int i = 0; i < Size; i++)
        {
            if (vUsers[i].UserName == _UserName)
            {
                vUsers[i]._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(vUsers);
        Size--;

        *this = _GetEmptyUserObject();

        delete[] vUsers;

        return true;

    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static clsUser* GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::eAll)
            return true;

        if ((Permission & this->Permissions) == Permission)
            return true;
        else
            return false;

    }

    

    void _addUserLogin() {
        fstream MyFile;
        MyFile.open("LogRejesters.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << _currentUserLogLine() << endl;
            MyFile.close();
        }
    }

    static LogUser* GetRegisterLogData() {
        LogUser* userlog = _loadLogUsersFromfile();
        return userlog;
    }

    static int LogUserCount(LogUser* vLogUser) {
        int i;
        for (i = 0; i < MaxNumberOfLoginsUser; i++) {
            if (vLogUser[i].Password.empty())
                break;
        }
        return i;
    }

};

