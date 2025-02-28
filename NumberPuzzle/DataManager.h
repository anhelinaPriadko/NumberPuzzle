#pragma once
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class DataManager
{
private:
	ifstream fileToRead;
	ofstream fileToWrite;

public:
	vector <string> numbers;

	DataManager(string pathToRead, string pathToWrite);
	~DataManager();

	void readData();
	void writeData(string number);
};

