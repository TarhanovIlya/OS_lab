#include"Creator_Class.h"
#include<iostream>

int main(int argc, char* argv[]) {

	char fileName[20];
	int employeesNum = 0;
	Creator creator;
	
	strcpy_s(fileName, argv[0]);

	
	employeesNum = atoi(argv[1]);

	
	creator.SetEmployeeNum(employeesNum);

	creator.OpenBin(fileName);

	creator.WriteToBin();
	
	

}