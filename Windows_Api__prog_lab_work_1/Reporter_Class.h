#pragma once

#include"Employee.h"
#include<iostream>
#include<fstream>
#include<istream>
#include<ostream>


class Reporter
{
	double HourSalary = 0.0;            
	char inFileName[50];
	std::ofstream outFile;
	std::ifstream inFile;
	int employeeNum = 0;

public:

	Reporter();
	~Reporter();

	void OpenBinFile(char* fileName);
	
	void OpenTxtFile(char* filename);

	void SetHourSalary(double HourSalary);

	std::ofstream& WriteToTxt();

};



Reporter::Reporter()
{
}

Reporter::~Reporter()
{
	inFile.close();
	outFile.close();

}

void Reporter::OpenBinFile(char* fileName) {
	
	strcpy_s(inFileName, fileName);

	inFile.open(fileName, std::ios::binary | std::ios::in);
	
	if (!inFile.is_open())
	{
		std::cout << "ERROR : FILE " << fileName << " IS NOT OPENED\n ";
	}

}

void Reporter::OpenTxtFile(char* fileName) {

	outFile.open(fileName, std::ios::out);

	if (!outFile.is_open())
	{
		std::cout << "ERROR : FILE " << fileName << " IS NOT OPENED\n ";
	}

}

std::ofstream& Reporter::WriteToTxt() {
	
	outFile << "Report of a file \""<<inFileName<<"\" :\n";

	inFile.read((char*)&employeeNum, sizeof(int));

	for (int i = 0; i < employeeNum; i++) {
		
		employee e;

		inFile.read((char*)&e, sizeof(employee));

		outFile << e.name << " " << e.num << " " << e.hours << " " << e.hours * HourSalary<<"\n";

	}
	
	return outFile;
}

void Reporter::SetHourSalary(double HourSalary) {

	this->HourSalary = HourSalary;

}

