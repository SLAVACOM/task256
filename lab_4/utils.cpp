#include "utils.h"
#include "constants.h"

#include <iostream>
#include <regex>
#include <fstream>
#include <cstring>
#include <string>


using namespace std;


void task(){
	regex valid_input("^[01]$");
	string input;
	char in_option, out_option;

	do {
		do {
			cout << "Введите '0' для ввода с консоли, '1' для ввода из файла: ";
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		in_option = input[0];
		
		do {
			cout << "Введите '0' для вывода на консоль, '1' для вывода в файл: ";
			getline(cin, input);
		} while (!regex_match(input, valid_input));
		out_option = input[0];


		cout << "dssd";
		char* dataBuffer = nullptr;


		if (in_option == '0') {
			if (!readFromConsole(dataBuffer) || !truncateAtExclamation(dataBuffer)) {
				delete[] dataBuffer;
				continue;
			}
		}
		else
		{
			if (!readFromFile(constants::input, dataBuffer) || !truncateAtExclamation(dataBuffer)
				) {
				delete[] dataBuffer;
				continue;
			}
		}

		if (dataBuffer != nullptr) {

			int firstCommaIndex{ -1 }, lastCommaIndex{ -1 };

			findCommas(dataBuffer, firstCommaIndex, lastCommaIndex);

			if (out_option == '0') {
				printConsole(firstCommaIndex,lastCommaIndex);
			}
			else if(out_option == '1')
			{
				writeToFile(constants::output, firstCommaIndex, lastCommaIndex);
			}
		}


		if (in_option == '0') {
			do {
				cout << "Введите '0' для повтора программы, '1' для завершения программы: ";
				getline(cin, input);
			} while (!regex_match(input, valid_input));
			in_option = input[0];

		}
	} while ( in_option != '1');
	
}

void findCommas(const char* data,int& firstCommaIndex, int& lastCommaIndex) {
	firstCommaIndex = { -1 };
	lastCommaIndex = { -1 };

	for (int i{ 0 }; i < '\n'; ++i) {
		if (data[i] == ',') {
			if (firstCommaIndex == -1) firstCommaIndex = i;
			lastCommaIndex = i;
		}
	}
}

void printConsole(int& firstCommaIndex, int& lastCommaIndex) {
	if (firstCommaIndex != -1) {
		std::cout << "Номер позиции первой запятой: " << firstCommaIndex + 1 << std::endl;
		std::cout << "Номер позиции последней запятой: " << lastCommaIndex + 1 << std::endl;
	}
	else
	{
		std::cout << "Запятые отсутствуют!!!" << std::endl;
	}
}

void writeToFile(const char* output, int& firstCommaIndex, int& lastCommaIndex) {
	ofstream outputFile(output);
	if (firstCommaIndex != -1) {
		outputFile << "Номер позиции первой запятой: " << firstCommaIndex + 1 << std::endl;
		outputFile << "Номер позиции последней запятой: " << lastCommaIndex + 1 << std::endl;
	}
	else
	{
		outputFile << "Запятые отсутствуют!!!" << std::endl;
	}
}

bool readFromFile(const char* filename, char*& buffer) {
	ifstream file(filename, ios::binary | ios::ate);
	if (!file.is_open()) {
		cout << "Ошибка при открытии файла с входными данными'" << endl;
		return false;
	}
	streamsize size = file.tellg();
	file.seekg(0, ios::beg);

	buffer = new (nothrow) char[size + 1];
	if (buffer == nullptr) {
		cout << "Не удалось выделить память для чтения файла" << endl;
		file.close();
		return false;
	}

	if (!file.read(buffer, size)) {
		cout << "Ошибка при чтении файла" << endl;
		delete[] buffer;
		buffer = nullptr;
		file.close();
		return false;
	}

	buffer[size] = '\0';
	file.close();
	return true;
}

bool readFromConsole(char*& buffer) {
	cout << "Введите данные: ";
	string input;
	getline(cin, input);

	buffer = new (nothrow) char[input.length() + 1];
	if (buffer == nullptr) {
		cout << "Не удалось выделить память для ввода данных" << endl;
		return false;
	}

	return true;
}

