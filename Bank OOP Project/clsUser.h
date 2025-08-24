#pragma once
#include <iostream>
#include "clsPerson.h"
#include "clsString.h" //String library header
#include "clsUtil.h"
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class clsUser : public clsPerson
{
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };
	enMode _Mode;
	string _UserName;
	string _Password;
	int _Permissions; 
	bool _MarkedForDelete = false;

    static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> UserData = clsString::Split(Line, Seperator);
        clsUser NewUser(UpdateMode, UserData[0], UserData[1], UserData[2], UserData[3], UserData[4], clsUtil::DecryptString(UserData[5],7), stoi(UserData[6]));
        return NewUser;
	}

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string Line = User.FirstName + Seperator + User.LastName + Seperator + User.Email + Seperator + User.Phone + Seperator + User._UserName + Seperator + clsUtil::EncryptString( User._Password,7) + Seperator + to_string(User._Permissions);
        return Line;
	}

    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> vUsers;
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            
            while (getline(MyFile, Line))
            {
                clsUser user = _ConvertLineToUserObject(Line);
                if (!user.IsEmpty())
                    vUsers.push_back(user);
            }
            MyFile.close();
        }
        return vUsers;
    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out);
        string DataLine;
        if (MyFile.is_open())
        {
            for (clsUser &U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }

    }

    void _Update()
    {
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
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

    string _PrepareLogInRecord(string Seperator = "#//#")
    {
        string Line = clsDate::GetSystemDateTimeString() + Seperator
            + UserName + Seperator
            + clsUtil::EncryptString(Password,7) + Seperator
            + to_string(Permissions);
        return Line;
    }
   
   struct stLoginRegisterRecord;
   static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        stLoginRegisterRecord record;
        vector<string> Data = clsString::Split(Line, Seperator);
        if (Data.size() >= 4)
        {
            record.DateTime = Data[0];
            record.UserName = Data[1];
            record.Password= clsUtil::DecryptString(Data[2],7);
            record.Permissions = stoi(Data[3]);
        }
        return record;
    }   

public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64,pLoginRegister=128
    };

    struct stLoginRegisterRecord
    {
		string DateTime;
        string UserName;
        string Password;
		int Permissions;
    };

    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string Password, int Permissions)
        : clsPerson(FirstName, LastName, Email, Phone)
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
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsUser user = _ConvertLineToUserObject(Line);
                if (user.UserName == UserName)
                {
                    MyFile.close();
                    return user;
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
                clsUser User = _ConvertLineToUserObject(Line);
                if (User.UserName == UserName &&  User.Password == Password)
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
        vector <clsUser> _vUsers;
        _vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : _vUsers)
        {
            if (U.UserName == _UserName)
            {
                U._MarkedForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(_vUsers);
        *this = _GetEmptyUserObject();
        return true;

    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }
    
    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::eAll)
            return true;
        else if ((Permission & this->Permissions) == Permission)
            return true;
        return false;

    }

    void RegisterLogIn()
    {
        string Line = _PrepareLogInRecord();
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << Line << endl;
            MyFile.close();
        }
    }

     static vector<clsUser::stLoginRegisterRecord> GetLoginRegisterList()
     {
         vector<clsUser::stLoginRegisterRecord> vLoginRegisterRecord;
         fstream MyFile;
         MyFile.open("LoginRegister.txt", ios::in);
         if (MyFile.is_open())
         {
             string Line;

             while (getline(MyFile, Line))
             {
                 clsUser::stLoginRegisterRecord user = _ConvertLoginRegisterLineToRecord(Line);
                     vLoginRegisterRecord.push_back(user);
             }
             MyFile.close();
         }
         return vLoginRegisterRecord;
     }

};
