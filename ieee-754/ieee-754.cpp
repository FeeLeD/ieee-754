#include "stdafx.h"
#include "iostream"
#include "bitset"
#include "math.h"
#include "ConvertingToBinary.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int operation;

	while (true) {
		cout << "0 - преобразование из 10-ой системы в 2-ую" << endl;
		cout << "Выберите операцию: ";
		cin >> operation;
		switch (operation)
		{
		case 0: ConvertingToBinary instance;
			instance.convertingToBinary();
			break;
		default:
			cout << "Некорректная операция" << endl;
			break;
		}
	}
}
 