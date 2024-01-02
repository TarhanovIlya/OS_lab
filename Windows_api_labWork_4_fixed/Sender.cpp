#include <iostream>
#include <fstream>
#include<Windows.h>
#include<string>

//#define DEBUG

using namespace std;


struct killyourself {
	string content;

};


		//there problem. first message dont get written

int main(int argc, char* argv[]) {
	std::cout << "sender(fixed) " << argv[1] << " Started\n\n ";
	std::cout << "File to send messages to: " << argv[0] << '\n';

	HANDLE sMutex = OpenMutex(SYNCHRONIZE, FALSE, L"synchronMutex1");
#ifdef DEBUG
	if (sMutex == NULL) std::cout << "ERROR: synchronMutex1 == NULL\n";
#endif // DEBUG


	//open file to write messages
	std::ofstream out;
	//out.open(argv[0], std::ios::out | std::ios::binary | std::ios::app);

	//if (!out.is_open()) {
	//	std::cout << "Error: message file is not opened\n";
	//	throw std::_Xruntime_error;
	//}
	////



	//send mutex to receiver ( == this sender is ready)
	ReleaseMutex(sMutex);
	//


	//wait for signal to start from receiver
	HANDLE startAll = OpenEvent(SYNCHRONIZE, FALSE, L"startAll");
#ifdef DEBUG
	std::cout << "DEBUG				waitStarted\n";
#endif // DEBUG
	WaitForSingleObject(startAll, INFINITE);
#ifdef DEBUG
	std::cout << "DEBUG				waitSuccessful\n";
#endif // DEBUG
	//

	HANDLE semaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, L"semaphore_1");
#ifdef DEBUG
	if (semaphore == NULL) std::cout << "ERROR: semaphore == NULL\n";
#endif // DEBUG



	char toContinue;
	killyourself messageStr;
	char buffer[100];
	while (1) {
		std::cout << "continue? (y / any key) : \n";
		std::cin >> toContinue;
		getchar();

		if (toContinue == 'y') {
			std::cout << "enter message: \n";
			getline(cin, messageStr.content);
			

			
#ifdef DEBUG
			if (!out.is_open()) {
				cout << "ERROR			out is not opened";
			}
#endif // DEBUG


			
			//write to file here
			out.open(argv[0], std::ios::out | std::ios::binary | std::ios::app);
			out.write((char*)&messageStr,sizeof(killyourself));
			out.close();

			
			
			ReleaseSemaphore(semaphore, 1, NULL);
		}
		else {
			break;
		}
	}

	out.close();
	std::cout << "sender" << argv[1] << " ended work			PRESS ANY KEY TO CONTINUE";
	std::cin.get();
}