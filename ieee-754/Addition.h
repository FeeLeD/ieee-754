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

		string result = addBinaryNumbers(first_binary, second_binary);
		carry_bit = "0";

		int sum = first + second;
		int* rf = reinterpret_cast<int *>(&sum);

		cout << "Результат (с помощью bitset)   : " << bitset<32>(*rf) << endl;
		cout << "Результат (собственная функция): " << result << endl;
	};

	string addBinaryNumbers(string first_binary, string second_binary) {
		ConvertingToBinary instance;
		int last_index = first_binary.length() - 1;
		string first_number;
		string second_number;
		string result;

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

		return instance.reverse(result);
	};

	int getDecimal(string binary) {
		int decimal = 0;
		int length = binary.length();
		for (int i = binary.length() - 1, power = 0; i >= 0; i--, power++) {
			if (binary[i] == '1') {
				decimal += pow(2, power);
			}
		}
		return decimal;
	}
public:
	string carry_bit;
	void makeAddition() {
		float first, second;
		cout << "Введите первое число: ";
		cin >> first;
		cout << "Введите второе число: ";
		cin >> second;

		bool isInteger = (first == (int)first) &&
			(second == (int)second);

		if (isInteger) {
			addIntNumbers(first, second);
		}
		else {
			ConvertingToBinary instance;
			string first_ieee = instance.convertToIEEE(first);
			string second_ieee = instance.convertToIEEE(second);
			string first_exponent;
			string first_mantissa;
			string second_exponent;
			string second_mantissa;


			for (int i = 1; i < 32; i++) {
				if (i < 9) {
					first_exponent += first_ieee[i];
					second_exponent += second_ieee[i];
				}
				else {
					first_mantissa += first_ieee[i];
					second_mantissa += second_ieee[i];
				}
			}

			int first_decimal = getDecimal(first_exponent);
			int second_decimal = getDecimal(second_exponent);


			string exponent_difference_binary;
			if (first_decimal > second_decimal) {
				second_exponent = instance.makeReverseCodeFrom(second_exponent);
				second_exponent = instance.makeAdditionalCodeFrom(second_exponent);
			}
			else {
				first_exponent = instance.makeReverseCodeFrom(first_exponent);
				first_exponent = instance.makeAdditionalCodeFrom(first_exponent);
			}
			exponent_difference_binary = addBinaryNumbers(first_exponent, second_exponent);
			carry_bit = "0";
			int decimal_difference = getDecimal(exponent_difference_binary);

			string temp_value = first_mantissa;
			first_mantissa = "1";
			first_mantissa += temp_value;

			temp_value = second_mantissa;
			second_mantissa = "1";
			second_mantissa += temp_value;

			string result_exponent;
			if (first_decimal > second_decimal) {
				result_exponent = first_exponent;
				temp_value = second_mantissa;
				second_mantissa = "";
				for (int i = 0; i < decimal_difference; i++) {
					second_mantissa += "0";
				}
				second_mantissa += temp_value;
				second_mantissa = second_mantissa.substr(0, 24);
			}
			else {
				result_exponent = second_exponent;
				temp_value = first_mantissa;
				first_mantissa = "";
				for (int i = 0; i < decimal_difference; i++) {
					first_mantissa += "0";
				}
				first_mantissa += temp_value;
				first_mantissa = first_mantissa.substr(0, 24);
			}

			string result_mantissa = addBinaryNumbers(first_mantissa, second_mantissa);
			
			
			if (carry_bit == "1") {
				result_exponent = instance.makeAdditionalCodeFrom(result_exponent);
				carry_bit = "0";
				result_mantissa = result_mantissa.substr(0, 23);
			} 
			else {
				result_mantissa = result_mantissa.substr(1, 23);
			}
			string s = "0";
			
			float sum = first + second;
			int* rf = reinterpret_cast<int *>(&sum);

			cout << "Результат (с помощью bitset)   :" << bitset<32>(*rf) << endl;
			cout << "Результат (собственная функция):" << s.append(result_exponent).append(result_mantissa) << endl;
		}
	}
};

