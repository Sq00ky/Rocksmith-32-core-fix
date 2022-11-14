#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <locale>
#include <string>

using namespace std;

HANDLE GetProcesHandleName() {
    HANDLE ProcessHandle;
    PROCESSENTRY32 procEntry;
    HANDLE allProcesses;
    while (ProcessHandle != NULL) {
    procEntry.dwSize = sizeof(PROCESSENTRY32);
    allProcesses = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

        if (Process32First(allProcesses, &procEntry) == TRUE) {
            while (Process32Next(allProcesses, &procEntry) == TRUE) {
                wchar_t newtargetProcName[1024] = L"Rocksmith2014.exe";

                if (wcscmp(procEntry.szExeFile, newtargetProcName) == 0) {
                    cout << "Process ID Found! PID: " << procEntry.th32ProcessID << "\n";
                    ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry.th32ProcessID);
                    return ProcessHandle;
                }
            }
        }
    }
}

int main()
{
    unsigned long lProcessAffinityMask = 2147483647;
    HANDLE rocksmith;
    cout << "[+] Running - Please launch Rocksmith 2014";
    rocksmith = GetProcesHandleName();
    SetProcessAffinityMask(rocksmith, lProcessAffinityMask);
    cout << "Updated Processor Affinity County";
    exit(0);

}
