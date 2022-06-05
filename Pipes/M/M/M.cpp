#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>

std::string getResult(std::string input) {
 std::string res;
 while (!input.empty()) {
  auto end = find(input.begin(), input.end(), ' ');
  std::string tmp = input.substr(0, end - input.begin());
  if (end == input.end()) break;
  end++;
  input.erase(input.begin(), end);
  int num = stoi(tmp, nullptr, 10);
  res+=std::to_string(num * 7) + " ";
 }
 return res;
}

int getError(BOOL fConnected) {
 if (!fConnected)
 {
  switch (GetLastError())
  {
  case ERROR_NO_DATA:
   fprintf(stdout, "ConnectNamedPipe: ERROR_NO_DATA");
   return 0;
   break;

  case ERROR_PIPE_CONNECTED:
   fprintf(stdout,
    "ConnectNamedPipe: ERROR_PIPE_CONNECTED");
   return 0;
   break;

  case ERROR_PIPE_LISTENING:
   fprintf(stdout,
    "ConnectNamedPipe: ERROR_PIPE_LISTENING");
   return 0;
   break;

  case ERROR_CALL_NOT_IMPLEMENTED:
   fprintf(stdout,
    "ConnectNamedPipe: ERROR_CALL_NOT_IMPLEMENTED");
   return 0;
   break;

  default:
   fprintf(stdout, "ConnectNamedPipe: Error %ld\n",
    GetLastError());
   return 0;
   break;
  }
 }
}


int main() {

 const int BUFFSIZE = 512;

 // Буфер для передачи данных через канал
 char   szBuf[BUFFSIZE];

 // Создаем канал Pipe для чтения
 HANDLE hNamedPipe3;
 while ((hNamedPipe3 = CreateFile("\\\\.\\pipe\\$Pipe3$", // адрес строки имени файла 
  PIPE_ACCESS_INBOUND, // режим доступа 
  FILE_SHARE_READ | FILE_SHARE_WRITE, // режим совместного использования файла
  NULL, // дескриптор защиты  
  OPEN_EXISTING, // параметры создания 
  FILE_ATTRIBUTE_NORMAL, // атрибуты файла 
  NULL // идентификатор файла с атрибутами
 )) == INVALID_HANDLE_VALUE) {
 }
 // Если возникла ошибка, выводим ее код и зваершаем
  // работу приложения
 if (hNamedPipe3 == INVALID_HANDLE_VALUE)
 {
  fprintf(stdout, "CreateNamedPipe: Error THIS %ld\n",
   GetLastError());
  return 0;
 }
 // Выводим сообщение о начале процесса создания канала
 fprintf(stdout, "Waiting for connect...\n");

 // Ожидаем соединения со стороны клиента
 BOOL fConnected = ConnectNamedPipe(hNamedPipe3, NULL);
 getError(fConnected);

 // Выводим сообщение об успешном создании канала
 fprintf(stdout, "\nConnected. Waiting for command...\n");
 std::string input;
 // Получаем очередную команду через канал Pipe
 if (ReadFile(hNamedPipe3, szBuf, BUFFSIZE, NULL, NULL))
 {
  std::string str(szBuf);
  std::cout << "M reieve: " << str << "\n";
  input = getResult(str);
  std::cout << "M sent: " << input << "\n";
 }
 else
 {
  fprintf(stdout, "ReadFile: Error %ld\n",
   GetLastError());
 }

 // Создаем канал Pipe для записи
 HANDLE hNamedPipe4 = CreateNamedPipe(
  "\\\\.\\pipe\\$Pipe4$", // адрес строки имени канала 
  PIPE_ACCESS_OUTBOUND,   // режим открытия канала 
  PIPE_TYPE_BYTE,         // режим работы канала 
  1,                      // максимальное количество реализаций канала 
  BUFFSIZE,               // размер выходного буфера в байтах 
  BUFFSIZE,               // размер входного буфера в байтах 
  0,                      // время ожидания в миллисекундах 
  NULL);                  // адрес переменной для атрибутов защиты

 // Если возникла ошибка, выводим ее код и зваершаем
  // работу приложения
 if (hNamedPipe4 == INVALID_HANDLE_VALUE)
 {
  fprintf(stdout, "CreateNamedPipe: Error %ld\n",
   GetLastError());
  return 0;
 }
 // Ожидаем соединения со стороны клиента
 fConnected = ConnectNamedPipe(hNamedPipe4, nullptr);
 getError(fConnected);

 // Передаем введенную строку серверному процессу в качестве команды
 if (!WriteFile(hNamedPipe4, input.c_str(), strlen(szBuf),
  NULL, NULL)) {
  std::cout << "WriteFile:ERROR!\n";
 }

 CloseHandle(hNamedPipe3);
 CloseHandle(hNamedPipe4);

 system("pause");
 return 0;
}

