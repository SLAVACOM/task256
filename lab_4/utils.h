#pragma once


void task();

void findCommas(const char* data, int& firstCommaIndex, int& lastCommaIndex);

void printConsole(int& firstCommaIndex, int& lastCommaIndex);

void writeToFile(const char* output, int& firstCommaIndex, int& lastCommaIndex);

bool readFromFile(const char* filename, char*& buffer);

bool readFromConsole(char*& buffer);

bool truncateAtExclamation(char*& buffer);
