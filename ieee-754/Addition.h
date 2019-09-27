#include "iostream"
#include "math.h"
#include "string"
#include "bitset"
#include "ConvertingToBinary.h"

#pragma once
class Addition
{
private:
	void addIntNumbers(int first, int second) {
		ConvertingToBinary instance;
		string first_binary = instance.convertIntToBinary(first);
		string second_binary = instance.convertIntToBinary(second);

		int last_index = first_binary.length() - 1;
		string first_number;
		string second_number;
		string result;
		string carry_bit;

		for (int i = last_index; i >= 0; i--) {
			first_number = first_binary[i];
			second_number = second_binary[i];

			if (first_number == "0" && second_number == "0") {
				if (carry_bit == "1") {
					result += '1';
					carry_bit = '0';
				}
				else
					result += '0';
			}

			if ((first_number == "1" && second_number == "0") ||
				(first_number == "0" && second_number == "1")) {
				if (carry_bit == "1") {
					result += '0';
				}
				else
					result += '1';
			}

			if (first_number == "1" && second_number == "1") {
				if (carry_bit == "1") {
					result += '1';
				}
				else {
					result += '0';
					carry_bit = '1';
				}
			}
		}
		if (carry_bit == "1" && (first >= 0 && second >= 0)) {
			result += '1';
		}

		cout << "–езультат: " << instance.reverse(result) << endl;
	};
public:
	void makeAddition() {
		float first, second;
		cout << "¬ведите первое число: ";
		cin >> first;
		cout << "¬ведите второе число: ";
		cin >> second;

		bool isInteger = (first == (int)first) &&
			(second == (int)second);

		if (isInteger) {
			addIntNumbers(first, second);
		}
	}
};

