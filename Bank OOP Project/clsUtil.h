#pragma once
#include <iostream>
#include "clsDate.h"
using namespace std;

class clsUtil
{
public:

	static void Srand()
	{
		srand((unsigned)time(NULL));

	}

	static int RandomNumber(int From, int To)
	{
		int randNum = rand() % (To - From + 1) + From;
		return randNum;
	}

	enum enCharType { SLetter = 1, Cletter, Digit, Scharacter, Mix };

	static char GetRandomCharacter(enCharType e)
	{
		if (e == Mix)
		{
			e = (enCharType)RandomNumber(1, 3);

		}
		switch (e)
		{
		case SLetter: return (char)RandomNumber(97, 122);
		case Cletter: return (char)RandomNumber(65, 90);
		case Scharacter: return (char)RandomNumber(33, 47);
		case Digit:return RandomNumber(48, 57);

		}
	}

	static string GenerateWord(enCharType CharType, short Length)
	{
		string word = "";
		for (int i = 0; i < Length; i++)
		{

			word = word + GetRandomCharacter(CharType);

		}
		return word;
	}

	static string GenerateKey(enCharType CharType)
	{
		string key = "";
		key = GenerateWord(CharType, 4) + '-';
		key = key + GenerateWord(CharType, 4) + '-';
		key = key + GenerateWord(CharType, 4) + '-';
		key = key + GenerateWord(CharType, 4);

		return key;

	}

	static void GenerateKeys(short NumberOfKeys, enCharType CharType)
	{

		for (int i = 1; i <= NumberOfKeys; i++)
		{
			cout << "Key[" << i << "] : ";
			cout << GenerateKey(CharType) << endl;

		}
	}

	static void Swap(int& a, int& b)
	{
		int temp = a;
		a = b;
		b = temp;
	}
	static void Swap(double& a, double& b)
	{
		double temp = a;
		a = b;
		b = temp;
	}
	static void Swap(char& a, char& b)
	{
		char temp = a;
		a = b;
		b = temp;
	}
	static void Swap(string& a, string& b)
	{
		string temp = a;
		a = b;
		b = temp;
	}
	static void Swap(clsDate& Date1, clsDate& Date2)
	{
		clsDate Temp = Date1;
		Date1 = Date2;
		Date2 = Temp;
	}

	static void ShuffleArray(int Arr[100], int Length)
	{
		for (int i = 0; i < Length; i++)
		{
			Swap(Arr[RandomNumber(1, Length) - 1], Arr[RandomNumber(1, Length) - 1]);
		}
	}
	static void ShuffleArray(string Arr[100], int Length)
	{
		for (int i = 0; i < Length; i++)
		{
			Swap(Arr[RandomNumber(1, Length) - 1], Arr[RandomNumber(1, Length) - 1]);
		}
	}

	static int ReadPositiveNumber(string Message)
	{
		int Number;
		do
		{
			cout << Message;
			cin >> Number;
			if (Number <= 0)
			{
				cout << "Please Enter Positive Number" << endl;
			}
		} while (Number <= 0);
		return Number;
	}

	static void FillArrayWithRandomNumbers(int Arr[100], int Length, int Min, int Max)
	{
		for (int i = 0; i < Length; i++)
		{
			Arr[i] = RandomNumber(Min, Max);

		}
	}

	static void FillArrayWithRandomWords(string	 Arr[100], int Length, enCharType CharType, int lengthOfWord)
	{
		for (int i = 0; i < Length; i++)
		{
			Arr[i] = GenerateWord(CharType, lengthOfWord);

		}
	}

	static void FillArrayWithRandomKeys(string Arr[100], int Length, enCharType CharType)
	{
		for (int i = 0; i < Length; i++)
		{
			Arr[i] = GenerateKey(CharType);
		}
	}

	static string  Tabs(short NumberOfTabs)
	{
		string t = "";

		for (int i = 1; i < NumberOfTabs; i++)
		{
			t = t + "\t";
			cout << t;
		}
		return t;

	}
	static string EncryptString(string str, int key)
	{
		string encrypted = "";
		for (int i = 0; i < str.length(); i++)
		{
			encrypted += char((int)str[i] + key);
		}
		return encrypted;
	}
	static string DecryptString(string str, int key)
	{
		string decrypted = "";
		for (int i = 0; i < str.length(); i++)
		{
			decrypted += char((int)str[i] - key);
		}
		return decrypted;
	}

	static string NumberToText(long long Number)
	{

		if (Number == 0)
		{
			return "";
		}

		if (Number >= 1 && Number <= 19)
		{
			string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
		"Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
		  "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

			return  arr[Number] + " ";

		}

		if (Number >= 20 && Number <= 99)
		{
			string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
			return  arr[Number / 10] + " " + NumberToText(Number % 10);
		}

		if (Number >= 100 && Number <= 199)
		{
			return  "One Hundred " + NumberToText(Number % 100);
		}

		if (Number >= 200 && Number <= 999)
		{
			return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
		}

		if (Number >= 1000 && Number <= 1999)
		{
			return  "One Thousand " + NumberToText(Number % 1000);
		}

		if (Number >= 2000 && Number <= 999999)
		{
			return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
		}

		if (Number >= 1000000 && Number <= 1999999)
		{
			return  "One Million " + NumberToText(Number % 1000000);
		}

		if (Number >= 2000000 && Number <= 999999999)
		{
			return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
		}

		if (Number >= 1000000000 && Number <= 1999999999)
		{
			return  "One Billion " + NumberToText(Number % 1000000000);
		}
		else
		{
			return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
		}


	}
};
