#include <iostream>
#include"Reporter_Class.h"

int main(int argc, char* argv[]) {

	char inFile[50];
	char outFile[50];
	double HourSalary = 0.0;
	Reporter reporter;

	strcpy_s(inFile, argv[0]);
	strcpy_s(outFile, argv[1]);
	HourSalary = atof(argv[2]);



	reporter.OpenBinFile(inFile);
	reporter.OpenTxtFile(outFile);

	reporter.SetHourSalary(HourSalary);

	reporter.WriteToTxt();
}