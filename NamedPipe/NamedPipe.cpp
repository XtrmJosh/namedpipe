// NamedPipe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream>

#define CONNECTING_STATE 0
#define READING_STATE 1
#define WRITING_STATE 2
#define INSTANCES 4
#define PIPE_TIMEOUT 5000
#define BUFSIZE 512

HANDLE hNamedPipe;

int _tmain(int argc, _TCHAR* argv[])
{
	hNamedPipe = CreateNamedPipe(L"\\\\.\\pipe\\pipename", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, 64, 64, PIPE_TIMEOUT, NULL);
	if (hNamedPipe == NULL || hNamedPipe == INVALID_HANDLE_VALUE)
	{
		std::cout << "Creation of named pipe failed" << std::endl;
		std::cout << "Last Error: " << GetLastError() << std::endl;
		std::system("PAUSE");
		return 1;
	}
	BOOL res = ConnectNamedPipe(hNamedPipe, NULL);
	if (!res)
	{
		std::cout << "Connection to named pipe failed" << std::endl;
		std::system("PAUSE");
		CleanUp();
		return 1;
	}
	const char *data = "HELLO WORLD\0";
	DWORD bytesWritten = 0;
	res = WriteFile(hNamedPipe, data, BUFSIZE, &bytesWritten, NULL);
	if (!res)
	{
		std::cout << "Sending data to named pipe failed" << std::endl;
		std::system("PAUSE");
		CleanUp();
		return 1;
	}
	else
	{
		std::cout << "Number of bytes written: " << bytesWritten << std::endl;
		std::cout << "Sent data" << data << std::endl;
		std::system("PAUSE");
		CleanUp();
		return 0;
	}
}

void CleanUp()
{
	CloseHandle(hNamedPipe);
}

