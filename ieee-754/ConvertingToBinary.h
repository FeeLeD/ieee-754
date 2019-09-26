#include "iostream"
#include "math.h"
#include "string"
#include "bitset"

using namespace std;

#pragma once

class ConvertingToBinary
{
public:
	void convertingToBinary() {
		double decimal_number;
		cout << "¬ведите число: ";
		cin >> decimal_number;

		string s;
		int e, m;

		if (decimal_number >= 0)
			s = "0";
		else {
			s = "1";
			decimal_number = -decimal_number;
		}

		int startIndex = 0, endIndex = 1;

		while (!(decimal_number >= interval(startIndex) && decimal_number <= interval(endIndex))) {
			startIndex++;
			endIndex++;
		}

		e = startIndex + 127;
		m = pow(2, 23) * (decimal_number - interval(startIndex)) / (interval(endIndex) - interval(startIndex));
		string result = s.append(convertToBinary(e, true)).append(convertToBinary(m, false));

		cout << "„исло в двоичном формате(самосто€тельно)  : " << result << endl << endl;
	}

	int interval(int power) {
		return pow(2, power);
	}

	string convertToBinary(int decimal_number, bool isExp) {
		string binary_number;
		while (decimal_number >= 1) {
			if (decimal_number % 2 == 0)
				binary_number += "0";
			if (decimal_number % 2 == 1)
				binary_number += "1";
			decimal_number /= 2;
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

	string reverse(string str) {
		string result;
		int length = str.length();
		for (int i = length - 1; i >= 0; i--) {
			result += str[i];
		}
		return result;
	}
};

