#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <cstring>

using namespace std;

#define NANO 10e9
constexpr long double RAM_TIME = 13.75 / NANO;
constexpr long double SSD_TIME = 150 / 10e7;
constexpr long double HDD_TIME = 520 / 10e8;

struct Comma final : std::numpunct<char>
{
    char do_decimal_point() const override { return ','; }
};

template <typename T>
long double testWrite(const string memoryType, const size_t dataBlockSize, vector<T> &vec, string filename = "")
{
    ofstream fileOut;
    vector<long double> timePoints;
    auto localStart = chrono::high_resolution_clock::now();
    auto localStop = chrono::high_resolution_clock::now();

    if (memoryType == "HDD" || memoryType == "SSD")
    {
        fileOut.open(filename, ios::out | ios::binary);

        if (!fileOut.is_open())
        {
            return -EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < dataBlockSize; i++)
    {
        T tempElement = rand() % (dataBlockSize * 2) - dataBlockSize;

        if (memoryType == "RAM")
        {
            localStart = chrono::high_resolution_clock::now();
            vec[i] = tempElement;
            localStop = chrono::high_resolution_clock::now();
        }
        else if (memoryType == "HDD" || memoryType == "SSD")
        {
            localStart = chrono::high_resolution_clock::now();
            fileOut << tempElement;
            localStop = chrono::high_resolution_clock::now();
        }

        timePoints.push_back(chrono::duration<long double>(localStop - localStart).count());
    }

    if (memoryType == "HDD" || memoryType == "SSD")
    {
        fileOut.close();
    }

    long double totalTime = 0;
    for (const auto &i : timePoints)
    {
        totalTime += i;
    }

    return totalTime;
}

template <typename T>
long double testRead(const string memoryType, const size_t dataBlockSize, vector<T> &vec, string filename = "")
{
    ifstream fileIn;
    vector<long double> timePoints;
    auto localStart = chrono::high_resolution_clock::now();
    auto localStop = chrono::high_resolution_clock::now();

    if (memoryType == "HDD" || memoryType == "SSD")
    {
        fileIn.open(filename, ios::in | ios::binary);

        if (!fileIn.is_open())
        {
            return -EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < dataBlockSize; i++)
    {
        if (memoryType == "RAM")
        {
            localStart = chrono::high_resolution_clock::now();
            vec[i];
            localStop = chrono::high_resolution_clock::now();
        }
        else if (memoryType == "HDD" || memoryType == "SSD")
        {
            T tempElement = {};

            localStart = chrono::high_resolution_clock::now();
            fileIn >> tempElement;
            localStop = chrono::high_resolution_clock::now();
        }

        timePoints.push_back(chrono::duration<long double>(localStop - localStart).count());
    }

    if (memoryType == "HDD" || memoryType == "SSD")
    {
        fileIn.close();
    }

    long double totalTime = 0;
    for (const auto &i : timePoints)
    {
        totalTime += i;
    }

    return totalTime;
}

template <typename T>
void fillRand(vector<T> arr)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    vector<T> temp;
    for (size_t i = 0; i < arr.size(); i++)
    {
        temp.push_back(i);
    }
    shuffle(temp.begin(), temp.end(), std::default_random_engine(seed));
    for (size_t i = 0; i < arr.size(); i++)
    {
        arr[i] = temp[i];
    }
}

void printHeader()
{
    cout << "MemoryType;"
         << "BlockSize;"
         << "ElementType;"
         << "BufferSize;"
         << "LaunchNum;"
         << "Timer;"
         << "WriteTime(s);"
         << "AverageWriteTime(s);"
         << "WriteBandwidth(Mb/s);"
         << "AbsError(write)(s);"
         << "RelError(write)(%);"
         << "ReadTime(s);"
         << "AverageReadTime(s);"
         << "ReadBandwidth(Mb/s);"
         << "AbsError(read)(s);"
         << "RelError(read)(%);"
         << endl;
}

void printInfo(string memoryType, size_t blockSize, string elementType, size_t bufferSize, size_t launchNum, string timerType, long double writeTime, long double avgWriteTime, long double absErrorWrite, long double relErrorWrite, long double readTime, long double avgReadTime, long double absErrorRead, long double relErrorRead)
{
    long double writeBandwidth = (blockSize / avgWriteTime) / 1024 / 8 * 10;
    long double readBandwidth = (blockSize / avgReadTime) / 1024 / 8 * 10;

    if (memoryType == "SSD" || memoryType == "HDD")
    {
        writeBandwidth /= 10e2;
        readBandwidth /= 10e2;
    }

    cout << memoryType << ";"
         << blockSize << ";"
         << elementType << ";"
         << bufferSize << ";"
         << launchNum << ";"
         << timerType << ";"
         << writeTime << ";"
         << avgWriteTime << ";"
         << writeBandwidth << ";"
         << absErrorWrite << ";"
         << relErrorWrite << "%;"
         << readTime << ";"
         << avgReadTime << ";"
         << readBandwidth << ";"
         << absErrorRead << ";"
         << relErrorRead << "%;"
         << endl;
}

long double getAvgTimeFromVec(vector<long double> timePoints)
{
    long double avgTime = 0;
    for (const auto &i : timePoints)
    {
        avgTime += i;
    }
    avgTime /= timePoints.size();
    return avgTime;
}

long double getTotalTimeFromVec(vector<long double> timePoints)
{
    long double totalTime = 0;
    for (const auto &i : timePoints)
    {
        totalTime += i;
    }
    return totalTime;
}

void doTest(const string timerType, const string memoryType, const size_t blockSize, const size_t launchCount)
{
    size_t dataBlockSize = blockSize / sizeof(blockSize);
    vector<long double> timePointsWrite;
    vector<long double> timePointsRead;
    const string elementType = "int";
    const size_t bufferSize = sizeof(int);
    long double elementTime = 0;

    if (memoryType == "RAM")
    {
        vector<int> dataBlock(blockSize, 0);

        for (size_t i = 0; i < launchCount; i++)
        {
            timePointsWrite.push_back(testWrite(memoryType, dataBlockSize, dataBlock));
            timePointsRead.push_back(testRead(memoryType, dataBlockSize, dataBlock));
        }

        elementTime = RAM_TIME;
    }
    else if (memoryType == "SSD")
    {
        const string filename = "/tmp/memorytest.bin";
        vector<int> dataBlock;

        for (size_t i = 0; i < launchCount; i++)
        {
            timePointsWrite.push_back(testWrite(memoryType, dataBlockSize, dataBlock, filename));
            timePointsRead.push_back(testRead(memoryType, dataBlockSize, dataBlock, filename));
        }

        remove(filename.c_str());

        elementTime = SSD_TIME;
    }
    else if (memoryType == "HDD")
    {
        const string filename = "memorytest.bin";
        vector<int> dataBlock;

        for (size_t i = 0; i < launchCount; i++)
        {
            timePointsWrite.push_back(testWrite(memoryType, dataBlockSize, dataBlock, filename));
            timePointsRead.push_back(testRead(memoryType, dataBlockSize, dataBlock, filename));
        }

        remove(filename.c_str());

        elementTime = HDD_TIME;
    }

    const long double avgWriteTime = getAvgTimeFromVec(timePointsWrite);
    const long double avgReadTime = getAvgTimeFromVec(timePointsRead);
    const long double absErrorWrite = abs((elementTime * bufferSize * launchCount) - avgWriteTime);
    const long double absErrorRead = abs((elementTime * bufferSize * launchCount) - avgReadTime);
    const long double relErrorWrite = absErrorWrite / avgWriteTime * 100;
    const long double relErrorRead = absErrorRead / avgReadTime * 100;

    printHeader();

    for (size_t i = 0; i < launchCount; i++)
    {
        printInfo(
            memoryType,
            blockSize,
            elementType,
            bufferSize,
            i,
            timerType,
            timePointsWrite[i],
            avgWriteTime,
            absErrorWrite,
            relErrorWrite,
            timePointsRead[i],
            avgReadTime,
            absErrorRead,
            relErrorRead);
    }
}

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(NULL)));

    cout.imbue(std::locale(std::locale::classic(), new Comma));

    const string timerType = "chrono::high_resolution_clock";
    string memoryType("RAM");
    size_t blockSize(1024);
    size_t launchCount(10);

    for (size_t i = 0; i < static_cast<size_t>(argc); i++)
    {
        if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--memory-type"))
        {
            memoryType = argv[i + 1];
        }
        if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--block-size"))
        {
            blockSize = atoll(argv[i + 1]);
        }
        if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--launch-count"))
        {
            launchCount = atoll(argv[i + 1]);
        }
    }

    ofstream out(memoryType + ".csv");
    std::cout.rdbuf(out.rdbuf());

    if (memoryType == "RAM" || memoryType == "SSD" || memoryType == "HDD")
    {
        doTest(timerType, memoryType, blockSize, launchCount);
    }
    else
    {
        cerr << "Invalid input" << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}