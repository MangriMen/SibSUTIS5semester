#include <windows.h>
#include <ImageHlp.h>
#include <iostream>

using namespace std;

int main(int argc, PCHAR argv[]) {
  HANDLE hSrcFile = CreateFile((LPTSTR)argv[1], GENERIC_READ, FILE_SHARE_READ,
                               NULL, OPEN_EXISTING, 0, NULL);
  if (hSrcFile == INVALID_HANDLE_VALUE) {
    cerr << "Err code: " << GetLastError() << "\n";
    cerr << "Could not load " << argv[1] << "."
         << "\n";
    exit(0);
  }
  HANDLE hFileMap = CreateFileMapping(hSrcFile, NULL, PAGE_READONLY, 0, 0, NULL);
  PVOID pSrcFile = (PVOID)MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 0);

  IMAGE_DOS_HEADER *pDosHeader = (IMAGE_DOS_HEADER *)pSrcFile;
  PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)((PBYTE)pDosHeader + pDosHeader->e_lfanew);

  cout << hex << uppercase << fixed << showbase;

  PVOID BaseAddress = pSrcFile;
  cout << reinterpret_cast<DWORD_PTR>(BaseAddress) << " - Base Address"
       << "\n";

  cout << "\n"
       << "Export region:"
       << "\n";

  if (pNtHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size) {
    DWORD_PTR RVAExpDir = static_cast<DWORD_PTR>(
        pNtHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]
            .VirtualAddress);
    cout << RVAExpDir << " - RVA"
         << "\n";

    DWORD_PTR VAExpAddress = reinterpret_cast<DWORD_PTR>(
        ImageRvaToVa(pNtHdr, BaseAddress, static_cast<ULONG>(RVAExpDir), NULL));
    cout << VAExpAddress << " - VA"
         << "\n";

    PIMAGE_EXPORT_DIRECTORY ExpTable = (PIMAGE_EXPORT_DIRECTORY)VAExpAddress;

    string sName = reinterpret_cast<PCHAR>(ImageRvaToVa(pNtHdr, BaseAddress, ExpTable->Name, NULL));
    cout << "Name of PEF: " << sName << "\n";

    PCHAR *pNames = (PCHAR *)ImageRvaToVa(pNtHdr, BaseAddress, ExpTable->AddressOfNames, NULL);

    DWORD_PTR nNames = ExpTable->NumberOfNames;
    cout << "Exported data:"
         << "\n";

    PCHAR pName = nullptr;
    for (DWORD_PTR i = 0; i < nNames; i++, *pNames++) {
      pName = reinterpret_cast<PCHAR>(ImageRvaToVa(pNtHdr, BaseAddress, static_cast<ULONG>(reinterpret_cast<DWORD_PTR>(*pNames)), NULL));
      if (pName == nullptr) {
        break;
      }
      cout << pName << "\n";
    }
  } else {
    cout << "No export data"
         << "\n";
  }

  cout << "\n"
       << "Import region:"
       << "\n";

  if (pNtHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size) {
    DWORD_PTR RVAImpDir =
        pNtHdr->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT]
            .VirtualAddress;
    cout << RVAImpDir << " - RVA"
         << "\n";

    DWORD_PTR VAImpAddress = reinterpret_cast<DWORD_PTR>(
        ImageRvaToVa(pNtHdr, BaseAddress, static_cast<ULONG>(RVAImpDir), NULL));
    cout << VAImpAddress << " - VA"
         << "\n";
    PIMAGE_IMPORT_DESCRIPTOR ImpTable = (PIMAGE_IMPORT_DESCRIPTOR)VAImpAddress;

    string sName = reinterpret_cast<PCHAR>(
        ImageRvaToVa(pNtHdr, BaseAddress, ImpTable->Name, NULL));
    cout << "Name of PEF: " << sName << "\n";

    PCHAR *pNames = reinterpret_cast<PCHAR *>(
        ImageRvaToVa(pNtHdr, BaseAddress, ImpTable->FirstThunk, NULL));

    cout << "Imported data:"
         << "\n";

    PCHAR pName = nullptr;
    for (; (*pNames != nullptr); *(pNames++)) {
      pName = reinterpret_cast<PCHAR>(
                  ImageRvaToVa(pNtHdr, BaseAddress,
                               static_cast<ULONG>(reinterpret_cast<DWORD_PTR>(*pNames)), NULL)) +
              2;
      cout << pName << "\n";
    }
  } else {
    cout << "No import data"
         << "\n";
  }

  UnmapViewOfFile(pSrcFile);
  CloseHandle(hFileMap);
  CloseHandle(hSrcFile);

  return EXIT_SUCCESS;
}