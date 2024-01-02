#include<iostream>
#include"Windows.h"
#include"string"
#include<fstream>
#include<istream>

int main() {

	char BinFileName[30];
	char BinReportFileName[30];
	char TxtReportFileName[30];
	double HourSalary;
	int employeeNum;
	PROCESS_INFORMATION piCreator;
	STARTUPINFO siCreator;
	PROCESS_INFORMATION piReporter;
	STARTUPINFO siReporter;

	
	ZeroMemory(&siCreator, sizeof(STARTUPINFO));
	siCreator.cb = sizeof(STARTUPINFO);
	ZeroMemory(&siReporter, sizeof(STARTUPINFO));
	siReporter.cb = sizeof(STARTUPINFO);

	


	std::cout << "Enter .bin file name: ";
	std::cin >> BinFileName;
	//strcpy_s(BinFileName, "Employee.bin");
	std::cout << "Enter number of employee: ";
	std::cin >> employeeNum;
	//employeeNum = 1;

	
	
	char buffer[100];
	std::string commandLineStr="";
	size_t size= sizeof(buffer);
	std::string evenMoreTemp=BinFileName;
	commandLineStr = evenMoreTemp + " " + std::to_string(employeeNum);
	wchar_t wtext[100];
	size_t outsize;
	mbstowcs_s(&outsize, wtext, commandLineStr.c_str(), commandLineStr.length() + 1);
	LPWSTR commandLine=wtext;


	if (!CreateProcess(L"C:\\Users\\r1r2\\Desktop\\code\\Windows_Api__prog_lab_work_1\\x64\\Debug\\Creator.exe", commandLine, NULL, NULL, FALSE, NULL, NULL, NULL, &siCreator, &piCreator)) {
		std::cout << "ERROR: PROCESS IS NOT CREATED\n";
		return GetLastError();
	}
	
	WaitForSingleObject(piCreator.hThread, INFINITE);
	CloseHandle(piCreator.hThread);
	CloseHandle(piCreator.hProcess);




	// Creator stops here




	std::cout << "Enter .bin report file name: ";
	std::cin >> BinReportFileName;
	//strcpy_s(BinReportFileName, "Employee.bin");
	std::cout << "Enter .txt report file name: ";
	std::cin >> TxtReportFileName;
	//strcpy_s(TxtReportFileName, "EmployeeReport.txt");
	std::cout << "Enter hour salary ";
	std::cin >> HourSalary;
	//HourSalary = 2.0;


	commandLineStr.erase(0);

	
	std::string space= " ";
	commandLineStr = BinReportFileName + space+TxtReportFileName+space+ std::to_string(HourSalary);
	mbstowcs_s(&outsize, wtext, commandLineStr.c_str(), commandLineStr.length() + 1);
	LPWSTR commandLine2 = wtext;


	if (!CreateProcess(L"C:\\Users\\r1r2\\Desktop\\code\\Windows_Api__prog_lab_work_1\\x64\\Debug\\Reporter.exe", commandLine2, NULL, NULL, FALSE, NULL, NULL, NULL, &siReporter, &piReporter)) {
		std::cout << "ERROR: PROCESS IS NOT CREATED\n";
		return GetLastError();
	}

	WaitForSingleObject(piReporter.hThread, INFINITE);
	CloseHandle(piReporter.hThread);
	CloseHandle(piReporter.hProcess);




	//Reporter stops there




	std::cout << "\n";

	std::ifstream report(TxtReportFileName, std::ios::in);

	if (report.is_open()) {
		char mychar;
		while (report) {
			mychar = report.get();
			std::cout << mychar;
		}
	}

	Sleep(100000);
}
