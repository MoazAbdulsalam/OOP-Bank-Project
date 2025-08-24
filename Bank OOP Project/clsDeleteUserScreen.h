#pragma once
#include "clsScrean.h"
#include "clsUser.h"
#include <iomanip>
#include <iostream>
#include "clsInputValidate.h"

class clsDeleteUserScreen :  protected clsScreen
{
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << User.FirstName;
        cout << "\nLastName    : " << User.LastName;
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email;
        cout << "\nPhone       : " << User.Phone;
        cout << "\nUser Name   : " << User.UserName;
        cout << "\nPassword    : " << User.Password;
        cout << "\nPermissions : " << User.Permissions;
        cout << "\n___________________\n";

    }

public:

    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("\t  Delete User Screen");

        string UserName = "";

        cout << "\nPlease Enter UserName: ";
        UserName = clsInputValidate::ReadString();
        while (!clsUser::IsUserExist(UserName))
        {
            cout << "\nUser Is NOT Found, Choose another one: ";
            UserName = clsInputValidate::ReadString();
        }
        clsUser  user = clsUser::Find(UserName);
        _PrintUser(user);
        cout << "\nAre you sure you want to delete this user ?";
        char ans = 'n';
        cin >> ans;
        if (ans == 'Y' || ans == 'y')
        {
            if (user.Delete())
            {
                cout << "\nUser Deleted Successfully :-)\n";
                _PrintUser(user);
            }
            else
            {
                cout << "\nError User Was not Deleted\n";

            }
        }
    }

};

