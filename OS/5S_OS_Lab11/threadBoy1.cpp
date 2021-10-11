#include <iostream>
#include <chrono>
#include <windows.h>

int main()
{
    while (true)
    {
        std::cout << "Thread boy 1 " << std::chrono::high_resolution_clock::now().time_since_epoch().count() << "\n";
    }

    return EXIT_SUCCESS;
}