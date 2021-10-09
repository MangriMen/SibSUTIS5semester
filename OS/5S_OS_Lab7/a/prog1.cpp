#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    HINSTANCE lib1;

    string command;
    while (true)
    {
        cout << "Available commands: connect, disconnect, exit" << endl;
        cin >> command;

        if (command == "connect")
        {
            lib1 = LoadLibrary(TEXT("lib1.dll"));

            if (!lib1)
            {
                cerr << "Could not load dll 'lib1.dll'" << endl;
                return EXIT_FAILURE;
            }

            cout << "lib1.dll loaded." << endl;
        }
        else if (command == "disconnect")
        {
            if (lib1)
            {
                FreeLibrary(lib1);
            }
            cout << "lib1.dll unloaded." << endl;
        }
        else if (command == "exit")
        {
            break;
        }
    }

    if (lib1)
    {
        FreeLibrary(lib1);
    }

    return EXIT_SUCCESS;
}