#pragma once

#include <iostream>
#include "clsScrean.h"
#include <iomanip>
#include <fstream>
#include "clsBankClient.h"

class clsTransferLogScreen :protected clsScreen
{
    static void PrintTransferLogRecordLine(clsBankClient::stTransferLogComponent TransferLogRecord)
    {

        cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.Date;
        cout << "| " << setw(8) << left << TransferLogRecord.SAcct;
        cout << "| " << setw(8) << left << TransferLogRecord.DAcct;
        cout << "| " << setw(8) << left << TransferLogRecord.Amount;
        cout << "| " << setw(10) << left << TransferLogRecord.SBalance;
        cout << "| " << setw(10) << left << TransferLogRecord.DBalance;
        cout << "| " << setw(8) << left << TransferLogRecord.UserName;


    }
public:

    static void ShowTransferLogScreen()
    {


        vector <clsBankClient::stTransferLogComponent> vTransferLogRecord = clsBankClient::GetTransferLogList();

        string Title = "\tTransfer Log List Screen";
        string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

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

        if (vTransferLogRecord.size() == 0)
            cout << "\t\t\t\tNo Transfers Available In the System!";
        else
        {
            for (clsBankClient::stTransferLogComponent& Record : vTransferLogRecord)
            {

                PrintTransferLogRecordLine(Record);
                cout << endl;
            }
        }
            

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }
};

