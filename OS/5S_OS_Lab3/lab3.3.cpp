#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main()
{
    size_t childCount = 4;
    pid_t parentPid = getpid();
    for (size_t i = 0; i < childCount; i++)
    {
        if (getpid() == parentPid)
        {
            fork();
        }
    }
    pause();
    return EXIT_SUCCESS;
}