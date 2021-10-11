#include <windows.h>
#include <ImageHlp.h>
#include <iostream>

using namespace std;

int main(int argc, PCHAR argv[])
{
     LOADED_IMAGE LoadedImage;
     if (!MapAndLoad(argv[1], NULL, &LoadedImage, TRUE, TRUE))
     {
          cerr << "Could not load PE region."
               << "\n";
          exit(EXIT_FAILURE);
     }

     cout << hex << uppercase << fixed << showbase;

     PUCHAR BaseAddress = LoadedImage.MappedAddress;
     cout << reinterpret_cast<DWORD_PTR>(BaseAddress) << " - Base Address"
          << "\n";

     cout << "\n"
          << "Export region:"
          << "\n";

     if (LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size)
     {
          DWORD_PTR RVAExpDir = static_cast<DWORD_PTR>(
              LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT]
                  .VirtualAddress);
          cout << RVAExpDir << " - RVA"
               << "\n";

          DWORD_PTR VAExpAddress = reinterpret_cast<DWORD_PTR>(
              ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, static_cast<ULONG>(RVAExpDir), NULL));
          cout << VAExpAddress << " - VA"
               << "\n";

          PIMAGE_EXPORT_DIRECTORY ExpTable = (PIMAGE_EXPORT_DIRECTORY)VAExpAddress;

          string sName = reinterpret_cast<PCHAR>(ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->Name, NULL));
          cout << "Name of PEF: " << sName << "\n";

          PCHAR *pNames = (PCHAR *)ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ExpTable->AddressOfNames, NULL);

          DWORD_PTR nNames = ExpTable->NumberOfNames;
          cout << "Exported data:"
               << "\n";

          PCHAR pName = nullptr;
          for (DWORD_PTR i = 0; i < nNames; i++, *pNames++)
          {
               pName = reinterpret_cast<PCHAR>(ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, static_cast<ULONG>(reinterpret_cast<DWORD_PTR>(*pNames)), NULL));
               if (pName == nullptr)
               {
                    break;
               }
               cout << pName << "\n";
          }
     }
     else
     {
          cout << "No export data"
               << "\n";
     }

     cout << "\n"
          << "Import region:"
          << "\n";

     if (LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size)
     {
          DWORD_PTR RVAImpDir =
              LoadedImage.FileHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT]
                  .VirtualAddress;
          cout << RVAImpDir << " - RVA"
               << "\n";

          DWORD_PTR VAImpAddress = reinterpret_cast<DWORD_PTR>(
              ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, static_cast<ULONG>(RVAImpDir), NULL));
          cout << VAImpAddress << " - VA"
               << "\n";
          PIMAGE_IMPORT_DESCRIPTOR ImpTable = (PIMAGE_IMPORT_DESCRIPTOR)VAImpAddress;

          string sName = reinterpret_cast<PCHAR>(
              ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ImpTable->Name, NULL));
          cout << "Name of PEF: " << sName << "\n";

          PCHAR *pNames = reinterpret_cast<PCHAR *>(
              ImageRvaToVa(LoadedImage.FileHeader, BaseAddress, ImpTable->FirstThunk, NULL));

          cout << "Imported data:"
               << "\n";

          PCHAR pName = nullptr;
          for (; (*pNames != nullptr); *(pNames++))
          {
               pName = reinterpret_cast<PCHAR>(
                           ImageRvaToVa(LoadedImage.FileHeader, BaseAddress,
                                        static_cast<ULONG>(reinterpret_cast<DWORD_PTR>(*pNames)), NULL)) +
                       2;
               cout << pName << "\n";
          }
     }
     else
     {
          cout << "No import data"
               << "\n";
     }

     UnMapAndLoad(&LoadedImage);

     return EXIT_SUCCESS;
}