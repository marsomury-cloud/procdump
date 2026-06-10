#pragma once

#include <windows.h>

#include <string>

std::wstring BuildDefaultDumpPath();
bool WriteDumpFile(const std::wstring& dump_path, EXCEPTION_POINTERS* exception_pointers);
LONG WINAPI TopLevelExceptionHandler(EXCEPTION_POINTERS* exception_pointers);
