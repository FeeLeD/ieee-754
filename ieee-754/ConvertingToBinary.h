#include "iostream"
#include "math.h"
#include "string"
#include "bitset"

using namespace std;

#pragma once

class ConvertingToBinary
{
private:
	string GetS(int number) { return number >= 0 ? "0" : "1"; };

	int* GetIntervalPowersFrom(double number) {
		int startPower = -10, endPower = -9;
		while (!(number >= pow(2, startPower) && number < pow(2, endPower))) {
			startPower++;
			endPower++;
		}
		int* powers = new int[2]{ startPower, endPower };
		return powers;
	}

	string convertDoubleToBinary(int number, bool isExp) {
		string binary_number;
		while (number >= 1) {
			if (number % 2 == 0)
				binary_number += "0";
			if (number % 2 == 1)
				binary_number += "1";
			number /= 2;
		}

		if (isExp) {
			while (binary_number.length() < 8) {
				binary_number.append("0");
			}
		}
		else {
			while (binary_number.length() < 23) {
				binary_number.append("0");
			}
		}

		return reverse(binary_number);
	}

public:
	void converting() {
		double number;
		float number_bitset;
		cout << "Введите число: ";
		cin >> number;
		number_bitset = (float)number;
		bool isInteger = (number == (int)number);

		if (isInteger) {
			int decimal_number = (int)number;
			cout << "Число в двоичном формате(с помощью bitset)   : " << bitset<32>(decimal_number) << endl;
			cout << "Число в двоичном формате(собственная функция): " << convertIntToBinary(decimal_number) << endl;
		}
		else {
			string result = convertToIEEE(number);	
			
			int* rf = reinterpret_cast<int *>(&number_bitset);
			cout << "Число в двоичном формате(с помощью bitset)   : " << bitset<32>(*rf) << " (формат IEEE-754)" << endl;
		
			cout << "Число в двоичном формате(собственная функция): " << result << " (формат IEEE-754)" << endl;
		}
	}

	string convertIntToBinary(int number) {
		string binary_number;

		if (number >= 0) {
			while (number >= 1) {
				if (number % 2 == 0)
					binary_number += "0";
				if (number % 2 == 1)
					binary_number += "1";
				number /= 2;
			}

			int numberLength = binary_number.length();
			if (numberLength <= 32) {
				int difference = 32 - numberLength;
				for (int i = 0; i < difference; i++) {
					binary_number += "0";
				}
			}
			return reverse(binary_number);
		}
		else {
			string binary_number;
			number = -number;
			while (number >= 1) {
				if (number % 2 == 0)
					binary_number += "0";
				if (number % 2 == 1)
					binary_number += "1";
				number /= 2;
			}

			binary_number = reverse(binary_number);

			binary_number = makeReverseCodeFrom(binary_number);

			binary_number = makeAdditionalCodeFrom(binary_number);

			int numberLength = binary_number.length();
			if (numberLength <= 32) {
				int difference = 32 - numberLength;
				string value = binary_number;
				binary_number = "";
				for (int i = 0; i < difference; i++) {
					binary_number += '1';
				}
				binary_number += value;
			}

			return binary_number;
		}
	}

	string convertToIEEE(float number) {
		string s;
		int exponent, mantissa;

		s = GetS(number);
		if (s == "1")
			number = -number;

		int* powerOfTwo = GetIntervalPowersFrom(number);

		exponent = powerOfTwo[0] + 127;
		double b = (number - pow(2, powerOfTwo[0])) / (pow(2, powerOfTwo[1]) - pow(2, powerOfTwo[0]));
		mantissa = pow(2, 23) * (number - pow(2, powerOfTwo[0])) / (pow(2, powerOfTwo[1]) - pow(2, powerOfTwo[0]));

		bool isExponent = true;
		bool isMantissa = false;

		string result = s.append(convertDoubleToBinary(exponent, isExponent)).
			append(convertDoubleToBinary(mantissa, isMantissa));
		
		return result;
	}

	string reverse(string str) {
		string result;
		int length = str.length();
		for (int i = length - 1; i >= 0; i--) {
			result += str[i];
		}
		return result;
	}
	
	string makeReverseCodeFrom(string code) {
		int length = code.length();
		for (int i = 0; i < length; i++) {
			if (code[i] == '0')
				code[i] = '1';
			else
				code[i] = '0';
		}
		return code;
	}

	string makeAdditionalCodeFrom(string code) {
		int lastIndex = code.length() - 1;

		if (code[lastIndex] == '0')
			code[lastIndex] = '1';
		else {
			for (int i = lastIndex; i >= 0; i--) {
				if (code[i] == '0') {
					code[i] = '1';
					break;
				}
				code[i] = '0';
			}
		}

		return code;
	}
};

