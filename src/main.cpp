#include "dump_writer.hpp"

#include <cstdio>
#include <cwchar>
#include <string>

namespace {

void PrintUsage(const wchar_t* exe_name) {
    std::wprintf(L"Usage:\n");
    std::wprintf(L"  %ls --self [dump-path]\n", exe_name);
    std::wprintf(L"  %ls --crash\n", exe_name);
    std::wprintf(L"\n");
    std::wprintf(L"  --self   Write a minidump of this process.\n");
    std::wprintf(L"  --crash  Install a crash handler and trigger a test crash.\n");
}

int RunSelfDump(const wchar_t* dump_path_arg) {
    const std::wstring dump_path = dump_path_arg ? dump_path_arg : BuildDefaultDumpPath();
    return WriteDumpFile(dump_path, nullptr) ? 0 : 1;
}

__declspec(noinline) void TriggerCrash() {
    volatile int* invalid = nullptr;
    *invalid = 42;
}

int RunCrashDemo() {
    SetUnhandledExceptionFilter(TopLevelExceptionHandler);
    std::wprintf(L"Crash handler installed. Triggering test crash...\n");
    TriggerCrash();
    return 1;
}

}  // namespace

int wmain(int argc, wchar_t* argv[]) {
    if (argc < 2) {
        PrintUsage(argv[0]);
        return 1;
    }

    if (wcscmp(argv[1], L"--self") == 0) {
        const wchar_t* dump_path = (argc >= 3) ? argv[2] : nullptr;
        return RunSelfDump(dump_path);
    }

    if (wcscmp(argv[1], L"--crash") == 0) {
        return RunCrashDemo();
    }

    PrintUsage(argv[0]);
    return 1;
}
