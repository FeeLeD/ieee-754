#include "stdafx.h"
#include "iostream"
#include "string"
#include "bitset"
#include "math.h"
#include "fstream"
#include "ConvertingToBinary.h"
#include "Addition.h"

using namespace std;

void ShowInstruction();

int main()
{
	setlocale(LC_ALL, "Russian");
	int operation;
	ShowInstruction();

	while (true) {
		cout << endl;
		cout << "Введите номер операции: ";
		cin >> operation;
		
		if (operation == 0) {
			ConvertingToBinary instance_c;
			instance_c.converting();
		}
		else if (operation == 1) {
			Addition instance;
			instance.makeAddition();
		}
		else {
			return 0;
		}
	}
}

void ShowInstruction() {
	string line;
	ifstream in("\instruction.txt");
	if (in.is_open()) {
		while (getline(in, line)) {
			cout << line << endl;
		}
	}
	in.close();
}
 