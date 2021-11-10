#include <unistd.h>    /* to use pipe, getpid */
#include <sys/stat.h>  /* to use named pipe mkfifo */
#include <sys/types.h> /* to use open() */
#include <fcntl.h>     /* to use open() */
#include <stdio.h>     /*to use prinf */
#include <iostream>    /*to use cin, cout */
#include <string.h>    /*to use str function */
#include <errno.h>     /* to use with errno */
#include <thread>      /* to use thread */

#define PIPE1_PATH "/home/phongdang/pipe1"
#define PIPE2_PATH "/home/phongdang/pipe2"

int openPipe(const char *pipePathName, int flag)
{
    int fileDescriptor;
    fileDescriptor = open(pipePathName, flag);
    if (fileDescriptor == -1)
    {
        std::cout << "Error open pipe at " << pipePathName << " .Error code: " << errno << std::endl;
    };
    return fileDescriptor;
}

void writePipe(int writePipeDescriptor)
{
    while (true)
    {
        //preparing to get the string from keyboard
        std::string chatInput;
        getline(std::cin, chatInput);
        int writeBytes = write(writePipeDescriptor, chatInput.c_str(), strlen(chatInput.c_str()));
        //send the string to pipe
        if (writeBytes == -1)
        {
            std::cout << "Error writing to write end of write pipe" << errno << std::endl;
        }
        else
        {
            printf("Writing to pipe %d bytes \n", writeBytes);
        }
        sleep(1);
    }
}

void readPipe(int readPipeDescriptor)
{
    char buffer[100];
    while (true)
    {
        //preparing the buffer to put the string to after reading from pipe
        memset(buffer, '\0', 100);
        // memset(buffer, 0, 10);
        int readByte = read(readPipeDescriptor, &buffer, 10);
        if (readByte == -1)
        {
            std::cout << "Error reading from read end of read pipe" << errno << std::endl;
        }
        else
            std::cout << "Read " << readByte << " bytes from pipe :" << buffer << std::endl;
        sleep(1);
    }
}

int main(int argc, char *argv[])
{
    int chatter = *(argv[1]) - '0';
    int writePipeDescriptor, readFileDescriptor;
    switch (chatter)
    {
    case 0:
    {
        printf("PID %d, chatter 1: \n", getpid());
        //create pipe is done by chatter 0 only (this is just a hot fix to prevent error 17 EEXIST)
        if (mkfifo(PIPE1_PATH, S_IRUSR | S_IWUSR | S_IWGRP) == -1)
        { //create pipe for read/write/execute by owner, and others
            std::cout << ("cannot create pipe 1 \n") << errno << std::endl;
        };
        writePipeDescriptor = openPipe(PIPE1_PATH, O_WRONLY);
        readFileDescriptor = openPipe(PIPE2_PATH, O_RDONLY);
        std::thread readThread(readPipe, readFileDescriptor); //has to create thread and execute thread first.
        writePipe(writePipeDescriptor);
        readThread.join();
        break;
    }
    case 1:
    {
        printf("PID %d, chatter 2: \n", getpid());

        if (mkfifo(PIPE2_PATH, S_IRUSR | S_IWUSR | S_IWGRP) == -1)
        { //create pipe for read/write/execute by owner, and others
            std::cout << ("cannot create pipe 2 \n") << errno << std::endl;
        };
        readFileDescriptor = openPipe(PIPE1_PATH, O_RDONLY);
        writePipeDescriptor = openPipe(PIPE2_PATH, O_WRONLY);
        std::thread writeThread(writePipe, writePipeDescriptor);
        readPipe(readFileDescriptor);
        writeThread.join();
        break;
    }
    }
    return 0;
}