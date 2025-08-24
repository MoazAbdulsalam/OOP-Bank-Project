#pragma once  
#include <string>  
#include <iostream>
#include "clsDate.h"  
#include "clsString.h"

using namespace std;
class clsInputValidate
{
public:


    template <typename T>
    static bool IsNumberBetween(T number, T min, T max)
    {
        return (number >= min && number <= max);
    }

    template <typename T>
    static T ReadTemplateNumber(string messageIfFail = "Invalid input. Please enter Again: ")
    {
        T number;
        cin >> number;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << messageIfFail;
            cin >> number;
        }

        return number;
    }

    template <typename T>
    static T ReadNumberBetween(T min, T max, string messageIfFail = "Invalid input. Please enter Again: ")
    {
        T number = ReadTemplateNumber<T>(messageIfFail);

        while (!IsNumberBetween<T>(number, min, max))
        {
            cout << messageIfFail;
            number = ReadTemplateNumber<T>(messageIfFail);
        }

        return number;
    }
    /*static bool IsNumberBetween(short number, short min, short max)
    {
        return (number >= min && number <= max);
    }

    static bool IsNumberBetween(int number, int min, int max)
    {
        return (number >= min && number <= max);
    }

    static bool IsNumberBetween(double number, double min, double max)
    {
        return (number >= min && number <= max);
    }*/

    static bool IsDateBetween(clsDate date, clsDate start, clsDate end)
    {
        if (clsDate::CompareDates(start, end) == clsDate::enDateCompare::After)
        {
            clsDate::SwapDates(start, end);
        }
        if ((date.CompareDates(start) == clsDate::enDateCompare::After || date.CompareDates(start) == clsDate::enDateCompare::Equal)
            && (date.CompareDates(end) == clsDate::enDateCompare::Before || date.CompareDates(end) == clsDate::enDateCompare::Equal))
        {
            return true;

        }
        return false;
    }



    /*  static int ReadIntNumber(string messageIfFail="Invalid input. Please enter Again:")
      {
          int number;
          cin >> number;
          while (cin.fail())
          {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << messageIfFail;
              cin >> number;
          }
          return number;
      }
      static short ReadShortNumber(string messageIfFail = "Invalid input. Please enter Again:")
      {
          short number;
          cin >> number;
          while (cin.fail())
          {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << messageIfFail;
              cin >> number;
          }
          return number;
      }

      static double ReadDoubleNumber(string messageIfFail = "Invalid Input. Please Enter Again:")
      {
          double number;
          cin >> number;
          while (cin.fail())
          {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << messageIfFail;
              cin >> number;
          }
          return number;
      }
      static float ReadFloatNumber(string messageIfFail = "Invalid Input. Please Enter Again:")
      {
          float number;
          cin >> number;
          while (cin.fail())
          {
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              cout << messageIfFail;
              cin >> number;
          }
          return number;
      }*/



      //   static short ReadShortNumberBetween(short min, short max, string messageIfFail = "Invalid input. Please enter Again:")
      //   {
      //       short number = ReadShortNumber(messageIfFail);
      //       while (!IsNumberBetween(number, min, max))
      //       {
      //           cout << messageIfFail;
      //           number = ReadShortNumber(messageIfFail);
      //       }
      //       return number;
      //   }

      //   static int ReadIntNumberBetween( int min, int max,string messageIfFail = "Invalid input. Please enter Again:")
      //   {  
      //       int number = ReadIntNumber(messageIfFail);  
      //       while (!IsNumberBetween(number, min, max))  
      //       {  
      //           cout << messageIfFail;  
      //           number = ReadIntNumber(messageIfFail);  
      //       }  
      //       return number;  
         //}

    static bool IsValidDate(clsDate Date)
    {
        return clsDate::IsValidDate(Date);
    }
    static string ReadString()
    {
        string str = "";
        getline(cin >> ws, str);
        return str;
    }

};