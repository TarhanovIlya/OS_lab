#pragma once

#include "Employee.h"
#include<ostream>
#include<fstream>
#include<iostream>

class Creator
{
	std::ofstream file;
	int EmployeeNum = 0;

public:

	Creator();

	~Creator();

	void OpenBin(char* fname);

	void SetEmployeeNum(int employeeNum);

	employee CreateEmployee();

	std::ofstream& WriteToBin();
};

Creator::Creator() {

}

Creator::~Creator() {

	file.close();

};

void Creator::OpenBin(char *fname) {
	
	file.open(fname, std::ios::binary | std::ios::out);
	
	if (!file.is_open())
	{
		std::cout << "ERROR : FILE " << fname << " IS NOT OPEN\n";
	}
};

employee Creator::CreateEmployee() {
	
	char name[10];
	int num;
	double hours;

	std::cout << "name: ";
	std::cin >> name;
	std::cout << "num: ";
	std::cin >> num;
	std::cout << "hours: ";
	std::cin >> hours;

	employee a(num, name, hours);
	 
	return a;
	
};

std::ofstream& Creator::WriteToBin() {

	file.write((char*)&EmployeeNum, sizeof(int));
	
	for (int i = 0; i < EmployeeNum; i++)
	{
		employee e = CreateEmployee();
		file.write((char*)&e,sizeof(employee));
	}

	return file;

}

void Creator::SetEmployeeNum(int employeeNum) {

	this->EmployeeNum = employeeNum;

}
