#include "dump_writer.hpp"

#include <dbghelp.h>

#include <cstdio>
#include <cwchar>

#pragma comment(lib, "Dbghelp.lib")

std::wstring BuildDefaultDumpPath() {
    SYSTEMTIME st{};
    GetLocalTime(&st);

    wchar_t module_path[MAX_PATH]{};
    if (GetModuleFileNameW(nullptr, module_path, MAX_PATH) == 0) {
        return L"dumps\\selfdump.dmp";
    }

    std::wstring path(module_path);
    const std::size_t slash = path.find_last_of(L"\\/");
    const std::wstring directory = (slash == std::wstring::npos) ? L"." : path.substr(0, slash);

    wchar_t file_name[128]{};
    swprintf_s(
        file_name,
        L"selfdump-%04u%02u%02u-%02u%02u%02u.dmp",
        st.wYear,
        st.wMonth,
        st.wDay,
        st.wHour,
        st.wMinute,
        st.wSecond
    );

    const std::wstring candidate = directory + L"\\..\\dumps\\" + file_name;

    wchar_t normalized[MAX_PATH]{};
    const DWORD length = GetFullPathNameW(candidate.c_str(), MAX_PATH, normalized, nullptr);
    if (length > 0 && length < MAX_PATH) {
        return normalized;
    }

    return candidate;
}

bool WriteDumpFile(const std::wstring& dump_path, EXCEPTION_POINTERS* exception_pointers) {
    HANDLE dump_file = CreateFileW(
        dump_path.c_str(),
        GENERIC_WRITE,
        0,
        nullptr,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        nullptr
    );

    if (dump_file == INVALID_HANDLE_VALUE) {
        std::fwprintf(stderr, L"CreateFileW failed for '%ls' (error=%lu)\n", dump_path.c_str(), GetLastError());
        return false;
    }

    MINIDUMP_EXCEPTION_INFORMATION exception_info{};
    exception_info.ThreadId = GetCurrentThreadId();
    exception_info.ExceptionPointers = exception_pointers;
    exception_info.ClientPointers = FALSE;

    const BOOL ok = MiniDumpWriteDump(
        GetCurrentProcess(),
        GetCurrentProcessId(),
        dump_file,
        static_cast<MINIDUMP_TYPE>(MiniDumpWithDataSegs | MiniDumpWithHandleData | MiniDumpWithThreadInfo),
        exception_pointers ? &exception_info : nullptr,
        nullptr,
        nullptr
    );

    const DWORD write_error = ok ? ERROR_SUCCESS : GetLastError();
    CloseHandle(dump_file);

    if (!ok) {
        std::fwprintf(stderr, L"MiniDumpWriteDump failed (error=%lu)\n", write_error);
        return false;
    }

    std::wprintf(L"Dump created: %ls\n", dump_path.c_str());
    return true;
}

LONG WINAPI TopLevelExceptionHandler(EXCEPTION_POINTERS* exception_pointers) {
    const std::wstring dump_path = BuildDefaultDumpPath();
    WriteDumpFile(dump_path, exception_pointers);
    return EXCEPTION_EXECUTE_HANDLER;
}
