#pragma once
#include "clsScrean.h"
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include <iomanip>
#include "clsListUsersScreen.h"
#include"clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsFindUserScreen.h"
class clsManageusersscreen : public clsScreen
{
   enum _enManageUsers{ eListUsers = 1 , eAddNewUser ,eDeletUser ,eUpdateUser ,eFindUser ,eMainMenue };

    static short _ReadManageUserMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadNumberBetween<short>(1, 6, "Enter Number between 1 to 6? ");
        return Choice;
    }

    static void _ShowListUserScreen()
    {
        clsListUsersScreen::ShowUsersList();
    }

    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUsersScreen();
    }

    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }

    static void _ShowUpdateUserScreen()
    {

    }

    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _GoBackToManageUserMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Manage Users Menue...\n";

        system("pause>0");
        ShowManageUserMenue();
    }

    static void _PerformManageUserOption(_enManageUsers op)
    {
        switch (op)
        {
        case clsManageusersscreen::eListUsers:
			system("cls");
			_ShowListUserScreen();
            _GoBackToManageUserMenue();

            break;
        case clsManageusersscreen::eAddNewUser:
            system("cls");
            _ShowAddNewUserScreen();
            _GoBackToManageUserMenue();

            break;
        case clsManageusersscreen::eUpdateUser:
            system("cls");
            _ShowUpdateUserScreen();
            _GoBackToManageUserMenue();
            break;
        case clsManageusersscreen::eDeletUser:
            system("cls");
            _ShowDeleteUserScreen();    
            _GoBackToManageUserMenue();
            break;
        case clsManageusersscreen::eFindUser:
            system("cls");
            _ShowFindUserScreen();
			_GoBackToManageUserMenue();
            break;
        case clsManageusersscreen::eMainMenue:
			
            break;
        default:
            break;
        }
    }

public:


    static void ShowManageUserMenue()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pManageUsers))
        {
            return;
        }

        system("cls");
        _DrawScreenHeader("\t\Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerformManageUserOption((_enManageUsers(_ReadManageUserMenueOption())));
    }
};

