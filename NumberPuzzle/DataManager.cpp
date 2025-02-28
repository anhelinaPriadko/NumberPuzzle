#include "DataManager.h"

DataManager::DataManager(string pathToRead, string pathToWrite):
	fileToRead(pathToRead), fileToWrite(pathToWrite)
{
    if (!fileToRead.is_open())
        throw runtime_error("Can`t open file for reading: " + pathToRead);
    if (!fileToWrite.is_open())
        throw runtime_error("Can`t open file for writing: " + pathToWrite);
}

DataManager::~DataManager()
{
    if (fileToRead.is_open())
        fileToRead.close();

    if (fileToWrite.is_open())
        fileToWrite.close();
}

void DataManager::readData()
{
    string number;
    while (fileToRead >> number)
    {
        numbers.push_back(number);
    }
}

void DataManager::writeData(string number)
{
    fileToWrite << number;
}