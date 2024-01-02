#include<Windows.h>
#include<iostream> 
#include<fstream>
#include<string>

//#define DEBUG








using namespace std;






struct killyourself {
	string content;

};












int main() {
	std::cout << "			Receiver started\n\n";
	std::string binFileName;

#ifdef DEBUG
	binFileName = "message.bin";
#else
	std::cout << "Enter name of bin file to read from :";
	std::cin >> binFileName;
#endif
	



	//create/erase file contents
	std::ofstream eraseMessage(binFileName, std::ios::binary | std::ios::trunc | std::ios::out);
	eraseMessage.close();
	//


	//create file to write/read messages
	std::ifstream messageFile{ binFileName,std::ios::binary | std::ios::in };
	//

	if (!messageFile.is_open())
	{
		std::cout << "Error: message file is not opened";
		throw std::_Xruntime_error;
	}
	//



	int senderNum = 0;
#ifdef DEBUG
	senderNum = 2;
#else
	std::cout << "Enter number of Sender processes :";
	std::cin >> senderNum;
#endif




	STARTUPINFO* siSenderArr = new STARTUPINFO[senderNum];
	PROCESS_INFORMATION* piSenderArr = new PROCESS_INFORMATION[senderNum];
	for (int i = 0; i < senderNum; i++) {
		ZeroMemory(&siSenderArr[i], sizeof(STARTUPINFO));
		siSenderArr[i].cb = sizeof(STARTUPINFO);
	}
	



	std::string temp = binFileName + " ";






	//create processes
	for (int i = 0; i < senderNum; i++) {

		std::string temp2 = temp + std::to_string(i);
		wchar_t lpwstrBinFile[100];
		size_t outsize;
		mbstowcs_s(&outsize, lpwstrBinFile, temp2.c_str(), temp2.length() + 1);


		if (!CreateProcess(L"C:\\Users\\r1r2\\Desktop\\code\\Windows_api_labWork_4_fixed\\x64\\Debug\\Sender.exe", lpwstrBinFile, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &siSenderArr[i], &piSenderArr[i])) {
			std::cout << "DEBUG		ERROR: PROCESS Sender " << i << " WAS NOT CREATED\n";
			std::cout << "		PRESS ANY KEY TO CONTINUE";
			std::cin.get();
			return GetLastError();
		}
	}


	HANDLE syncMutex = CreateMutex(NULL, FALSE, L"synchronMutex1");
	//wait for all processes to start and send a signal to continue their work
	for (int i = 0; i < senderNum; i++)
	{
		ReleaseMutex(syncMutex);

		WaitForSingleObject(syncMutex, INFINITE);
	}

	HANDLE startAllEv = CreateEvent(NULL, TRUE, TRUE, L"startAll");
	//



	//read from messageFile

		//create semaphore
	HANDLE semaphore = CreateSemaphore(NULL, 0, 10, L"semaphore_1");

	//

	char toContinue;
	killyourself mes;
	while (1) {

		while (1)
		{
			cout << "\n\n\n...Waiting for a new message...\n\n\n";

			DWORD waitRes = WaitForSingleObject(semaphore, 10000);
			// <-- if there are no messages in a minute, cycle will stop
			switch (waitRes)
			{
			case(WAIT_TIMEOUT): {
				std::cout << "10 seconds passed, but no messages appeared in file. End work? (y / any key) :";
				std::cin >> toContinue;
				if (toContinue == 'y') {
					goto exit;
				}
			}
			case(WAIT_OBJECT_0): {
				goto contCycle;
			}
			default:
				break;
			}

		}


	contCycle:


		std::cout << "continue? (y / any key) : ";
		std::cin >> toContinue;

		if (toContinue == 'y') {
			messageFile.read((char*)&mes, sizeof(killyourself));
			std::cout << mes.content << '\n';
		}
		else {
			break;
		}
	}
exit:







	//close processes
	HANDLE* hTread = new HANDLE[senderNum];
	HANDLE* hProcess = new HANDLE[senderNum];

	for (int i = 0; i < senderNum; i++) {
		hTread[i] = piSenderArr[i].hThread;
		hProcess[i] = piSenderArr[i].hProcess;

	}
	CloseHandle(semaphore);
	for (int i = 0; i < senderNum; i++) {
		TerminateProcess(hProcess, 0);
		CloseHandle(hTread[i]);
		CloseHandle(hProcess[i]);

	}
	CloseHandle(syncMutex);
	//

	delete hTread;
	delete hProcess;
	delete piSenderArr;
	delete siSenderArr;

	std::cout << "	receiver ended work		PRESS ANY KEY TO CONTINUE";
	std::cin.get();
}