#include <iostream>
#include <unistd.h>

int main()
{
    fork();

    pause();

    return EXIT_SUCCESS;
}