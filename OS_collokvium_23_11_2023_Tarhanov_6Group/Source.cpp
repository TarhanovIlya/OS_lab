#include<fstream>
#include<iostream>
#include<vector>
#include<Windows.h>
#include<string>

//using namespace std;

//#define DEBUG







CRITICAL_SECTION cs1;

std::ofstream out("out.dat", std::ios::app);




DWORD WINAPI solver(LPVOID param) {

	int threadIndex = (int)(INT_PTR)param;
	
	
	std::string fileName = "in_" + std::to_string(threadIndex)+ ".dat";
	std::ifstream in(fileName);
#ifdef DEBUG
	if (!in.is_open()) {
		std::cout << "ERROR			file " + fileName + " is not opened";
	}
#endif // DEBUG


	


	char operation;
	in >> operation;
	std::vector<double> digits;
	digits.reserve(50);
	double temp;
	while (!in.eof()) {
		in >> temp;
		digits.push_back(temp);
	}



	// calculate 
	double result = 0;

	switch (operation)
	{
	case('+'):
		for (int i = 0; i < digits.size(); i++) {
			result += digits[i];
		}
		break;


	case('*'):
		result = 1;
		for (int i = 0; i < digits.size(); i++) {
			result *= digits[i];
		}
		break;


	case('^'):
		for (int i = 0; i < digits.size(); i++) {
			result += digits[i]*digits[i];
		}
		break;


	default:
		EnterCriticalSection(&cs1);
		std::cout << "ERROR:		seems like file \" "<<fileName<<" \" have a unpredicted operation";
		LeaveCriticalSection(&cs1);
		break;
	}






	
	
	HANDLE mutex1 = OpenMutex(SYNCHRONIZE, FALSE, L"mutex1");
	WaitForSingleObject(mutex1, INFINITE);
#ifdef DEBUG
	if (mutex1 == NULL) {
		std::cout << "\n\nError: mutex1 is NULL\n\n";
		return GetLastError();
	}
#endif // DEBUG

	out << fileName << " result =" << result << '\n';
	ReleaseMutex(mutex1);


	return 0;
}



int main() {

	InitializeCriticalSection(&cs1);

	HANDLE mutex = CreateMutex(NULL, FALSE, L"mutex1");

	
	int n;
#ifdef DEBUG
	n = 4;
#endif
#ifndef DEBUG
	std::cout << "Enter N of files (starts from 0): ";
	std::cin >> n;


#endif // DEBUG

	
	
	
	HANDLE* threadArr = new HANDLE[n];
	DWORD* tId = new DWORD[n];

	
	
	//create threads
	for (int i = 0; i < n; i++) {
		threadArr[i] = CreateThread(NULL, NULL, solver, (LPVOID)(i), NULL, &tId[i]);
#ifdef DEBUG
		if (threadArr[i] == NULL) {
			std::cout << "ERROR:			thread" << i << "is not created";
			return GetLastError();
		}
#endif // DEBUG

	}
	//

	WaitForMultipleObjects(n, threadArr, TRUE, INFINITE);


	for (int i = 0; i < n; i++) {
		CloseHandle(threadArr[i]);
	}


	DeleteCriticalSection(&cs1);
	CloseHandle(mutex);
	delete threadArr;
	delete tId;

}