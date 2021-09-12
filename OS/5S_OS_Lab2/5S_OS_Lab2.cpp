#include <windows.h>
#include <iostream>
#include <string>
#include <atlstr.h>
#include <fileapi.h>

using namespace std;

#define WIDTH 12
#define DIV 1024

CString getArchitectureName(WORD arc) {
	switch (arc)
	{
	case PROCESSOR_ARCHITECTURE_AMD64:
		return CString(TEXT("x64 (AMD or Intel)"));
	case PROCESSOR_ARCHITECTURE_ARM:
		return CString(TEXT("ARM"));
	case PROCESSOR_ARCHITECTURE_ARM64:
		return CString(TEXT("ARM64"));
	case PROCESSOR_ARCHITECTURE_IA64:
		return CString(TEXT("Intel Itanium-based"));
	case PROCESSOR_ARCHITECTURE_INTEL:
		return CString(TEXT("x86"));
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		return CString(TEXT("Unknown architecture"));
	default:
		return CString(TEXT(""));
	}
}

int main() {
	CString winDir;
	CString winTempDir;
	SYSTEM_INFO systemInfo;
	MEMORYSTATUSEX memoryInfo;
	memoryInfo.dwLength = sizeof(memoryInfo);

	if (GetWindowsDirectory(winDir.GetBuffer(MAX_PATH), MAX_PATH) == 0) {
		winDir = "";
	}
	GetTempPath(MAX_PATH, winTempDir.GetBuffer(MAX_PATH));

	GlobalMemoryStatusEx(&memoryInfo);
	GetSystemInfo(&systemInfo);

	_tprintf(TEXT("Windows directory: %s\n"),
		(LPCTSTR)winDir);
	_tprintf(TEXT("Temp directory: %s\n"),
		(LPCTSTR)winTempDir);
	_tprintf(TEXT("\n"));

	_tprintf(TEXT("Number of processors: %u\n"),
		systemInfo.dwNumberOfProcessors);
	_tprintf(TEXT("Architecture: %s\n"),
		(LPCTSTR)getArchitectureName(systemInfo.wProcessorArchitecture));
	_tprintf(TEXT("\n"));

	_tprintf(TEXT("Application address lower border: %lp\n"),
		(LPCTSTR)systemInfo.lpMinimumApplicationAddress);
	_tprintf(TEXT("Application address upper border: %lp\n"),
		(LPCTSTR)systemInfo.lpMaximumApplicationAddress);
	_tprintf(TEXT("\n"));

	_tprintf(TEXT("There is  %*ld percent of memory in use.\n"),
		WIDTH, memoryInfo.dwMemoryLoad);
	_tprintf(TEXT("There are %*I64d total KB of physical memory.\n"),
		WIDTH, memoryInfo.ullTotalPhys / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of physical memory.\n"),
		WIDTH, memoryInfo.ullAvailPhys / DIV);
	_tprintf(TEXT("There are %*I64d total KB of paging file.\n"),
		WIDTH, memoryInfo.ullTotalPageFile / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of paging file.\n"),
		WIDTH, memoryInfo.ullAvailPageFile / DIV);
	_tprintf(TEXT("There are %*I64d total KB of virtual memory.\n"),
		WIDTH, memoryInfo.ullTotalVirtual / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of virtual memory.\n"),
		WIDTH, memoryInfo.ullAvailVirtual / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of extended memory.\n"),
		WIDTH, memoryInfo.ullAvailExtendedVirtual / DIV);

	return 0;
}