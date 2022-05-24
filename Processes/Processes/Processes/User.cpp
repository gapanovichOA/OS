#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

LPCSTR kill_path = "C:\\фпми учеба\\лабы\\OS\\Library\\Processes\\Processes\\Killer\\Debug\\Killer.exe";

void print_active_processes() {
 PROCESSENTRY32 process_entry = { 0 };
 process_entry.dwSize = sizeof(PROCESSENTRY32);
 HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
 Process32First(hSnap, &process_entry);
 std::wcout << "\nID:          NAME:  ";
 do {  
  std::wcout << std::setw(10) << process_entry.th32ProcessID << std::left << process_entry.szExeFile
   << '\n';
 } while (Process32Next(hSnap, &process_entry));
 CloseHandle(hSnap);
}

void kill(string command) {
 STARTUPINFOA sia = { 0 };
 PROCESS_INFORMATION proc_inf = { 0 };
 char* proc = (char*)command.c_str();
 if (CreateProcessA(kill_path, proc, NULL, NULL, FALSE, 0, NULL, NULL, &sia,
   &proc_inf)) {
   WaitForSingleObject(proc_inf.hProcess, INFINITE);
   CloseHandle(proc_inf.hProcess);
   CloseHandle(proc_inf.hThread);
 }
 _putenv_s("PROC_TO_KILL", "0");
}

int main() {
 SetEnvironmentVariable(L"PROC_TO_KILL", L"Telegram.exe ");
 print_active_processes();
 cout << "enter command: ";
 string command;
 cin >> command;
 kill(command);
 return 0;
}