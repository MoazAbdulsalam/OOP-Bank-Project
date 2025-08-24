#pragma once
#include<iostream>
#include<string>
#include<vector>

using namespace std;

class clsString
{
private:
	string _Value;
public:
	clsString()
	{
		_Value = "";
	}
	clsString(string Value)
	{
		_Value = Value;
	}
	void SetValue(string Value)
	{
		_Value = Value;
	}
	string GetValue()
	{
		return _Value;
	}
	__declspec(property(get = GetValue, put = SetValue)) string Value;

	short Length()
	{
		return _Value.length();
	}

	static short CountWords(string S1)
	{
		string delim = " ";
		short Counter = 0;
		short pos = 0;
		string sWord;
		while ((pos = S1.find(delim)) != string::npos)
		{
			sWord = S1.substr(0, pos);
			if (!sWord.empty())
				Counter++;
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
			Counter++;
		return Counter;
	}
	short CountWords()
	{
		return CountWords(_Value);
	}

	static void PrintFirstLetter(string txt)
	{
		bool isFirstLetter = true;
		for (short i = 0; i < txt.length(); i++)
		{
			if (txt[i] != ' ' && isFirstLetter)
			{
				cout << txt[i] << endl;
			}
			isFirstLetter = (txt.at(i) == ' ' ? true : false);
		}
	}
	void PrintFirstLetter()
	{
		PrintFirstLetter(_Value);
	}

	static void UpperFirstLetter(string& txt)
	{
		bool isFirstletter = true;
		for (int i = 0; i < txt.length(); i++)
		{
			if (txt.at(i) != ' ' && isFirstletter)
			{
				txt.at(i) = toupper(txt.at(i));
			}

			isFirstletter = (txt.at(i) == ' ' ? true : false);
		}
	}
	void UpperFirstLetter()
	{
		UpperFirstLetter(_Value);
	}

	static void LowerFirstLetter(string& txt)
	{
		bool isFirstletter = true;
		for (int i = 0; i < txt.length(); i++)
		{
			if (txt.at(i) != ' ' && isFirstletter)
			{
				txt.at(i) = tolower(txt.at(i));
			}

			isFirstletter = (txt.at(i) == ' ' ? true : false);
		}
	}
	void LowerFirstLetter()
	{
		LowerFirstLetter(_Value);
	}

	static void ToLower(string& txt)
	{
		for (int i = 0; i < txt.length(); i++)
		{
			txt.at(i) = tolower(txt.at(i));
		}
	}
	void ToLower()
	{
		ToLower(_Value);
	}

	static string ToUpper(string txt)
	{
		for (int i = 0; i < txt.length(); i++)
		{
			txt.at(i) = toupper(txt.at(i));
		}
		return txt;
	}
	void ToUpper()
	{
		_Value = ToUpper(_Value);
	}

	static char InvertedCase(char c)
	{

		return  isupper(c) ? tolower(c) : toupper(c);
	}
	static void InvertAllLettersCase(string& txt)
	{

		for (int i = 0; i < txt.length(); i++)
		{
			txt[i] = InvertedCase(txt[i]);
		}
	}
	void InvertAllLettersCase()
	{
		InvertAllLettersCase(_Value);
	}

	enum enWhatToCount { SmallLetters, CapitalLetters, All };
	static short CountLetters(string txt, enWhatToCount What = All)
	{
		short counter = 0;
		if (What == All)
		{
			return txt.length();
		}
		for (short i = 0; i < txt.length(); i++)
		{
			if (What == SmallLetters && islower(txt[i]))
				counter++;

			if (What == CapitalLetters && isupper(txt[i]))
				counter++;
		}
		return counter;
	}
	short CountLetters(enWhatToCount What)
	{
		return CountLetters(_Value, What);
	}

	static short CountSpecificLetterInAString(string txt, char letter, bool MatchCase = true)
	{
		short counter = 0;
		for (short i = 0; i < txt.length(); i++)
		{
			if (MatchCase)
			{
				if (txt[i] == letter)
					counter++;
			}
			else if (tolower(txt[i]) == tolower(letter))
				counter++;
		}
		return counter;
	}
	short CountSpecificLetterInAString(char letter, bool MatchCase)
	{
		return CountSpecificLetterInAString(_Value, letter, MatchCase);
	}

	static bool IsExist(string txt, char letter, bool MatchCase = true)
	{
		for (short i = 0; i < txt.length(); i++)
		{
			if (MatchCase)
			{
				if (txt[i] == letter)
					return true;
			}
			else if (tolower(txt[i]) == tolower(letter))
			{
				return true;
			}
		}
		return false;

	}
	void IsExist(char letter, bool MatchCase)
	{
		IsExist(_Value, letter, MatchCase);
	}

	static bool IsVowel(char c)
	{
		const string vowel = "aeiuo";
		return IsExist(vowel, c, false);
	}
	static short CountVowels(string txt)
	{
		short count = 0;
		for (short i = 0; i < txt.length(); i++)
		{
			if (IsVowel(txt[i]))
				count++;
		}
		return count;
	}
	short CountVowels()
	{
		return CountVowels(_Value);
	}

	static void PrintVowels(string txt)
	{
		short count = 0;
		for (short i = 0; i < txt.length(); i++)
		{
			if (IsVowel(txt[i]))
				cout << txt[i] << "  ";
		}
	}
	void PrintVowels()
	{
		PrintVowels(_Value);
	}

	static void PrintEachWord(string txt)
	{
		string delim = " ";
		short pos = 0;
		string sWord;
		while ((pos = txt.find(delim)) != string::npos)
		{
			sWord = txt.substr(0, pos);
			if (sWord != "")
				cout << sWord << endl;
			txt.erase(0, pos + delim.length());
		}
		if (txt != "")
			cout << txt << endl; // Print the last word if exists
	}
	void PrintEachWord()
	{
		PrintEachWord(_Value);
	}

	static vector<string> Split(string s1, string delim)
	{
		vector<string>Words;
		short pos = 0;
		string sword = "";

		while ((pos = s1.find(delim)) != string::npos)
		{
			sword = s1.substr(0, pos);
			//if (sword != "")
			//{
			Words.push_back(sword);
			//}
			s1.erase(0, pos + delim.length());
		}
		if (s1 != "")
		{
			Words.push_back(s1);
		}
		return Words;
	}
	vector<string> Split(string delim)
	{
		return Split(_Value, delim);
	}

	static string TrimLeft(string s1)
	{
		for (short i = 0; i < s1.length(); i++)
		{
			if (s1[i] != ' ')
			{
				return s1.substr(i, s1.length() - 1);
			}
		}
		return ""; // Return empty string if all characters are spaces
	}
	void TrimLeft()
	{
		_Value = TrimLeft(_Value);
	}

	static string TrimRight(string s1)
	{
		for (short i = s1.length() - 1; i >= 0; i--)
		{
			if (s1[i] != ' ')
			{
				return s1.substr(0, i + 1);
			}
		}
		return ""; // Return empty string if all characters are spaces
	}
	void TrimRight()
	{
		_Value = TrimRight(_Value);
	}

	static string Trim(string s1)
	{
		s1 = TrimLeft(s1);
		s1 = TrimRight(s1);
		return s1;
	}
	string Trim()
	{
		return Trim(_Value);
	}


	static string Join(vector<string> s1, string delim)
	{
		if (s1.empty()) return "";
		string result = s1[0];
		for (int i = 1; i < s1.size(); i++)
		{
			result += delim + s1[i];
		}
		return result;
	}

	static string Join(string s1[], short length, string delim)
	{

		string result = s1[0];
		for (int i = 1; i < length; i++)
		{
			result += delim + s1[i];
		}
		return result;
	}

	static string ReverseString(string s1)
	{
		string Reversed = "";
		vector<string> Words = Split(s1, " ");
		vector<string>::iterator it = Words.end();
		while (it != Words.begin())
		{
			--it;
			Reversed += *it + " ";
		}
		Reversed = Reversed.substr(0, Reversed.length() - 1);
		return Reversed;
	}
	string ReverseString()
	{
		return ReverseString(_Value);
	}

	static string ReplaceWords(string s1, string oldWord, string newWord)
	{
		vector<string> Words = Split(s1, " ");
		for (short i = 0; i < s1.length(); i++)
		{
			if (Words[i] == oldWord)
			{
				Words[i] = newWord;
			}
		}
		return Join(Words, " ");
	}
	string ReplaceWords(string oldWord, string newWord)
	{
		return ReplaceWords(_Value, oldWord, newWord);
	}

	static string RemovePunq(string s1)
	{
		string s2 = "";
		for (short i = 0; i < s1.length(); i++)
		{
			if (!ispunct(s1[i]))
				s2 += s1[i];
		}
		return s2;
	}
	string RemovePunq()
	{
		return RemovePunq(_Value);
	}

};
