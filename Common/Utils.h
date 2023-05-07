#pragma once
#include <string>
#include <format>

std::wstring GetLastErrorAsWString()
{
    const DWORD error = GetLastError();
    LPWSTR buffer = NULL;

    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, // Not relevant.
        error,
        0, // Use default order.
        (LPWSTR)&buffer,
        0, // No size, using FORMAT_MESSAGE_ALLOCATE_BUFFER.
        NULL); // No extra args.

    return std::wstring(buffer);
}

void MessageBoxWithErrorAndThrow(const std::wstring& message)
{
    MessageBoxW(
        NULL, // No owner window.
        message.c_str(),
        NULL, // Use default dialog box title.
        MB_OK);

    throw std::exception();
}

void MessageBoxWithWin32ErrorAndThrow(const std::wstring& message)
{
    const std::wstring fullMessage = std::vformat(L"{0}\n{1}", std::make_wformat_args(message, GetLastErrorAsWString()));
    MessageBoxWithErrorAndThrow(fullMessage);
}