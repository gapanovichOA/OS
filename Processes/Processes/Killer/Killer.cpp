#include<iostream>
#include<windows.h>
#include<TlHelp32.h>
#include<stdio.h>
#include<string.h>
#include<sstream>
#include<winbase.h>

void kill(const wchar_t* szExeName) {
 PROCESSENTRY32 pe = { 0 };
 pe.dwSize = { sizeof(PROCESSENTRY32) };
 HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);
 if (Process32First(hSnapshot, &pe)) {
  do {
   if (std::wcscmp(pe.szExeFile, szExeName) == 0) {
    HANDLE kill = nullptr;
    kill = OpenProcess(PROCESS_TERMINATE, TRUE, pe.th32ProcessID);
    if (kill != nullptr) {
     TerminateProcess(kill, 0);
     CloseHandle(kill);
    }
   }
  } while (Process32Next(hSnapshot, &pe));
 }
 CloseHandle(hSnapshot);
}

void killByID(int id) {
 HANDLE processToKill = OpenProcess(PROCESS_TERMINATE, FALSE, (DWORD)id);
 if (processToKill != NULL) {
  TerminateProcess(processToKill, 0);
  CloseHandle(processToKill);
 }
}

int main(int argc, char* argv[]) {

 LPCSTR name = "PROC_TO_KILL";
 const DWORD nSize = 65535;
 char lpBuffer[nSize];
 if (GetEnvironmentVariableA(name, lpBuffer, nSize)) {
  std::stringstream ss(lpBuffer);
  while (ss.getline(lpBuffer, nSize, ',')) {
   std::string str(lpBuffer);
   str += ".exe";
   std::wstring wstr = std::wstring(str.begin(), str.end());
   const wchar_t* wchr = wstr.c_str();
   kill(wchr);
  }
 }
 std::istringstream stream(argv[0]);
 int id = 0;
 stream >> id;
 if (id == 0) {
  std::string str(argv[0]);
  str += ".exe";
  std::wstring wstr = std::wstring(str.begin(), str.end());
  const wchar_t* wchr = wstr.c_str();
  kill(wchr);
 }
 else {
  killByID(id);
 }
 return 0;
}