#include <Windows.h>
#include <filesystem>
#include "../Common/Utils.h"

PROCESS_INFORMATION	gProcessInfo;

void CloseGameWithMessageAndThrow(const std::wstring& message)
{
    // If we already started the game, close it down.
    if (gProcessInfo.hThread != NULL)
    {
        TerminateProcess(gProcessInfo.hProcess, EXIT_SUCCESS);
    }

    MessageBoxWithWin32ErrorAndThrow(message);
}

void DoInjection(const std::string &dllPath)
{
    // Get process handle
    const HANDLE process = OpenProcess(
        PROCESS_ALL_ACCESS,
        FALSE,
        gProcessInfo.dwProcessId);
    if (process == NULL)
    {
        CloseGameWithMessageAndThrow(L"Could not open Daybreak process.");
    }

    const size_t length = dllPath.length();

    // Get address of LoadLibrary function.
    HMODULE hModule = GetModuleHandleW(L"kernel32.dll");
    if (hModule == NULL)
    {
        CloseGameWithMessageAndThrow(L"Could not get kernel32.dll module handle.");
    }
    LPVOID loadLibAddress = (LPVOID)GetProcAddress(hModule, "LoadLibraryA");
    if (loadLibAddress == NULL)
    {
        CloseGameWithMessageAndThrow(L"Could not get LoadLibraryA address.");
    }

    // Allocate memory within Daybreak's virtual address space.
    LPVOID arg = (LPVOID)VirtualAllocEx(
        process,
        NULL, // Automatically determine where to allocate region.
        length,
        MEM_COMMIT | MEM_RESERVE,
        PAGE_READWRITE);
    if (arg == NULL)
    {
        CloseGameWithMessageAndThrow(L"Could not reserve memory within Daybreak's virtual address space.");
    }

    // Write path for LoadLibraryA in previously allocated memory.
    BOOL result = WriteProcessMemory(
        process,
        arg,
        dllPath.c_str(),
        length,
        NULL); // Don't need to know how much was written.
    if (!result)
    {
        CloseGameWithMessageAndThrow(L"Could not write DLL path for LoadLibraryA.");
    }

    // Inject.
    HANDLE hThread = CreateRemoteThread(
        process,
        NULL, // Use default security descriptor.
        NULL, // Use default size.
        (LPTHREAD_START_ROUTINE)loadLibAddress,
        arg,
        0, // Run immediately after creation.
        NULL); // Don't need the thread ID.
    if (hThread == NULL)
    {
        CloseGameWithMessageAndThrow(L"Could not create remote thread in Daybreak's process.");
    }

    // Wait for injection to be fully complete.
    if (WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)
    {
        CloseGameWithMessageAndThrow(L"Failed waiting on DLL thread.");
    }
    CloseHandle(hThread);

    // Clean up after ourselves.
    result = VirtualFreeEx(
        process,
        arg,
        0, // Free the entire region.
        MEM_RELEASE);
    if (!result)
    {
        CloseGameWithMessageAndThrow(L"Could not release previously allocated memory.");
    }
    CloseHandle(process);

    // Let Daybreak start up.
    if (ResumeThread(gProcessInfo.hThread) == -1)
    {
        CloseGameWithMessageAndThrow(L"Could not resume Daybreak's main thread.");
    }
}

BOOL CreateDaybreakProcess(LPCWSTR appName, STARTUPINFO* startupInfo)
{
    return CreateProcessW(
        appName,
        NULL, // No command line args.
        NULL, // No special process attributes.
        NULL, // No special thread attributes.
        FALSE, // Don't inherit handles.
        CREATE_SUSPENDED, // Resume after injection.
        NULL, // Use current environment.
        NULL, // Start in same directory.
        startupInfo,
        &gProcessInfo);
}

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    const std::filesystem::path currentDir = std::filesystem::current_path();
    const std::wstring daybreakPath = currentDir.wstring() + L"\\DaybreakDX-en.exe";

    STARTUPINFO startupInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    ZeroMemory(&gProcessInfo, sizeof(gProcessInfo));
    startupInfo.cb = sizeof(startupInfo);

    BOOL success = CreateDaybreakProcess(daybreakPath.c_str(), &startupInfo);
    if (!success)
    {
        // Fall-back to original EXE on failure.
        const std::wstring daybreakOriginalPath = currentDir.wstring() + L"\\DaybreakDX.exe";
        success = CreateDaybreakProcess(daybreakOriginalPath.c_str(), &startupInfo);
        if (!success)
        {
            CloseGameWithMessageAndThrow(L"Failed to start Daybreak.");
        }
    }

    success = SetProcessAffinityMask(gProcessInfo.hProcess, 0x1); // CPU 0 only.
    if (!success)
    {
        CloseGameWithMessageAndThrow(L"Failed to set process affinity mask.");
    }

    success = SetPriorityClass(gProcessInfo.hProcess, HIGH_PRIORITY_CLASS);
    if (!success)
    {
        CloseGameWithMessageAndThrow(L"Failed to set process priority class.");
    }

    const std::string dllPath = currentDir.string() + "\\DaybreakFixer.dll";
    if (!std::filesystem::exists(dllPath))
    {
        CloseGameWithMessageAndThrow(L"Could not find DLL.");
    }
    
    DoInjection(dllPath);

    CloseHandle(gProcessInfo.hProcess);
    CloseHandle(gProcessInfo.hThread);

    return EXIT_SUCCESS;
}