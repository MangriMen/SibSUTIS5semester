#include <iostream>
#include <string>
#include <inttypes.h>
#include <windows.h>
#include <thread>

int globalVar = 0;

void incVar(int repeatCount)
{
    for (size_t i = 0; i < repeatCount; i++)
    {
        globalVar++;
        printf_s("Thread #%" PRIu32 " incremented, globalVar = %d\n", (*(uint32_t *)&std::this_thread::get_id()), globalVar);
    }
}

int main(void)
{
    globalVar = 0;
    std::thread testThread1(incVar, 10);
    std::thread testThread2(incVar, 10);
    std::thread testThread3(incVar, 10);

    printf("Thread #1 id:%" PRIu32 "\n       #2 id:%" PRIu32 "\n       #3 id:%" PRIu32 "\n",
           (*(uint32_t *)&testThread1.get_id()),
           (*(uint32_t *)&testThread2.get_id()),
           (*(uint32_t *)&testThread3.get_id()));

    testThread1.join();
    testThread2.join();
    testThread3.join();

    std::cout << "Expected value: " << 10 * 3 << "\n";
    std::cout << "Resulting value: " << globalVar << "\n";

    return EXIT_SUCCESS;
}
