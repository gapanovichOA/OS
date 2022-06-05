#include "windows.h"
#include <iostream>

LPCSTR A_path = "C:\\фпми учеба\\лабы\\OS\\Library\\Pipes\\A\\A\\Debug\\A.exe";
LPCSTR M_path = "C:\\фпми учеба\\лабы\\OS\\Library\\Pipes\\M\\M\\Debug\\M.exe";
LPCSTR S_path = "C:\\фпми учеба\\лабы\\OS\\Library\\Pipes\\S\\S\\Debug\\S.exe";
LPCSTR P_path = "C:\\фпми учеба\\лабы\\OS\\Library\\Pipes\\P\\P\\Debug\\P.exe";


int main() {
 PROCESS_INFORMATION pi1 = { 0 }, pi2 = { 0 }, pi3 = { 0 }, pi4 = { 0 };
 STARTUPINFO sa1 = { 0 }, sa2 = { 0 }, sa3 = { 0 }, sa4 = { 0 };

 const int BUFFSIZE = 512;

 // Буфер для передачи данных через канал
 char   szBuf[BUFFSIZE];

 HANDLE hNamedPipe1 = CreateNamedPipe(
  "\\\\.\\pipe\\$Pipe1$", // адрес строки имени канала 
  PIPE_ACCESS_OUTBOUND,   // режим открытия канала 
  PIPE_TYPE_BYTE,         // режим работы канала 
  1,                      // максимальное количество реализаций канала 
  BUFFSIZE,               // размер выходного буфера в байтах 
  BUFFSIZE,               // размер входного буфера в байтах 
  0,                      // время ожидания в миллисекундах 
  NULL);                  // адрес переменной для атрибутов защиты

  // Если возникла ошибка, выводим ее код и зваершаем
  // работу приложения
 if (hNamedPipe1 == INVALID_HANDLE_VALUE)
 {
  fprintf(stdout, "CreateNamedPipe: Error Main %ld\n",
   GetLastError());
  return 0;
 }

 if (!CreateProcess(P_path,   // module name
  NULL,        // Command line
  NULL,           // Process handle not inheritable
  NULL,           // Thread handle not inheritable
  FALSE,          // Set handle inheritance to FALSE
  0,              // No creation flags
  NULL,           // Use parent's environment block
  NULL,           // Use parent's starting directory 
  &sa1,            // Pointer to STARTUPINFO structure
  &pi1)           // Pointer to PROCESS_INFORMATION structure
  ) {
  fprintf(stdout, "CreateProcess: Error P %ld\n",
   GetLastError());
 }
 
 ConnectNamedPipe(hNamedPipe1, NULL);

 const char* data = "1 2 3 4 5 6 7";

 if (!WriteFile(hNamedPipe1, data, strlen(data),
  0, NULL)) {
  fprintf(stdout, "WriteFile: Error %ld\n",
   GetLastError());
 }

 CloseHandle(hNamedPipe1);

 if (!CreateProcess(A_path, NULL,
  NULL, NULL, FALSE,
  0, NULL, NULL,
  &sa2, &pi2)) {
  fprintf(stdout, "CreateProcess: Error A %ld\n",
   GetLastError());
 }

 if (!CreateProcess(M_path, NULL,
  NULL, NULL, FALSE,
  0, NULL, NULL,
  &sa3, &pi3)) {
  fprintf(stdout, "CreateProcess: Error M %ld\n",
   GetLastError());
 }

 if (!CreateProcess(S_path, NULL,
  NULL, NULL, FALSE,
  0, NULL, NULL,
  &sa4, &pi4)) {
  fprintf(stdout, "CreateProcess: Error S %ld\n",
   GetLastError());
 }

 HANDLE hNamedPipe5;
 while ((hNamedPipe5 = CreateFile(
  "\\\\.\\pipe\\$Pipe5$",
  PIPE_ACCESS_INBOUND,
  FILE_SHARE_READ,
  NULL,
  OPEN_EXISTING,
  FILE_ATTRIBUTE_NORMAL,
  NULL
 )) == INVALID_HANDLE_VALUE) {
 }

 // Если возникла ошибка, выводим ее код и зваершаем
 // работу приложения
 if (hNamedPipe5 == INVALID_HANDLE_VALUE) {
  fprintf(stdout, "CreateFile: Error Main %ld\n",
   GetLastError());
  return 1;
 }

 if (!ReadFile(hNamedPipe5, szBuf, BUFFSIZE,
  0, NULL)) {
  fprintf(stdout, "ReadFile: Error %ld\n",
   GetLastError());
 }

 std::string res(szBuf);
 std::cout << "\nMain recieved: " << res << "\n";

 CloseHandle(hNamedPipe5);
 system("pause");
 return 0;
}
