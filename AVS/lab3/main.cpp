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
constexpr long double FLASH_TIME = 9 / 10e6;

constexpr size_t KB_ = 1024;
constexpr size_t MB_ = 1024 * 1024;
constexpr size_t GB_ = 1024 * 1024 * 1024;

struct Comma final : std::numpunct<char>
{
    char do_decimal_point() const override { return ','; }
};

vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

bool memoryTypeIsRam(const string &memoryType)
{
    return memoryType == "RAM";
}

template <typename T>
long double testWrite(const string memoryType, const size_t dataBlockSize, vector<T> &vec, string filename = "")
{
    ofstream fileOut;
    vector<long double> timePoints;
    auto localStart = chrono::high_resolution_clock::now();
    auto localStop = chrono::high_resolution_clock::now();

    if (!memoryTypeIsRam(memoryType))
    {
        fileOut.open(filename, ios::out | ios::binary);

        if (!fileOut.is_open())
        {
            return -EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < dataBlockSize; i++)
    {
        const T tempElement = rand() % (dataBlockSize * 2) - dataBlockSize;

        if (memoryTypeIsRam(memoryType))
        {
            localStart = chrono::high_resolution_clock::now();
            vec[i] = tempElement;
            localStop = chrono::high_resolution_clock::now();
        }
        else
        {
            localStart = chrono::high_resolution_clock::now();
            fileOut << tempElement;
            localStop = chrono::high_resolution_clock::now();
        }

        timePoints.push_back(chrono::duration<long double>(localStop - localStart).count());
    }

    if (!memoryTypeIsRam(memoryType))
    {
        fileOut.close();
    }

    long double totalTime = 0;
    for (const auto &point : timePoints)
    {
        totalTime += point;
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

    if (!memoryTypeIsRam(memoryType))
    {
        fileIn.open(filename, ios::in | ios::binary);

        if (!fileIn.is_open())
        {
            return -EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < dataBlockSize; i++)
    {
        if (memoryTypeIsRam(memoryType))
        {
            localStart = chrono::high_resolution_clock::now();
            const T &_ [[maybe_unused]] = vec[i];
            localStop = chrono::high_resolution_clock::now();
        }
        else
        {
            T tempElement = {};

            localStart = chrono::high_resolution_clock::now();
            fileIn >> tempElement;
            localStop = chrono::high_resolution_clock::now();
        }

        timePoints.push_back(chrono::duration<long double>(localStop - localStart).count());
    }

    if (!memoryTypeIsRam(memoryType))
    {
        fileIn.close();
    }

    long double totalTime = 0;
    for (const auto &point : timePoints)
    {
        totalTime += point;
    }

    return totalTime;
}

long double getAvgTimeFromVec(vector<long double> timePoints)
{
    long double avgTime = 0;
    for (const auto &point : timePoints)
    {
        avgTime += point;
    }
    avgTime /= timePoints.size();
    return avgTime;
}

size_t parseBlockSize(string blockSize)
{
    size_t prefixPos = blockSize.find_first_not_of("0123456789");
    size_t blockSizeNum = atoll(blockSize.c_str());

    if (prefixPos != string::npos)
    {
        string prefixStr = blockSize.substr(prefixPos, 2);
        std::transform(prefixStr.begin(), prefixStr.end(), prefixStr.begin(), ::toupper);

        if (prefixStr == "KB")
        {
            blockSizeNum *= KB_;
        }
        else if (prefixStr == "MB")
        {
            blockSizeNum *= MB_;
        }
        else if (prefixStr == "GB")
        {
            blockSizeNum *= GB_;
        }
    }

    return blockSizeNum;
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
         << "RelError(read)(%)"
         << endl;
}

void printInfo(string memoryType, size_t blockSize, string elementType, size_t bufferSize, size_t launchNum, string timerType, long double writeTime, long double avgWriteTime, long double absErrorWrite, long double relErrorWrite, long double readTime, long double avgReadTime, long double absErrorRead, long double relErrorRead)
{
    long double writeBandwidth = (blockSize / avgWriteTime) / 1024 / 8;
    long double readBandwidth = (blockSize / avgReadTime) / 1024 / 8;

    if (!memoryTypeIsRam(memoryType))
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
         << relErrorRead << "%"
         << endl;
}

void doTest(const string timerType, const string memoryType, const size_t blockSize, const size_t launchCount, const string tempFilename = "")
{
    const size_t dataBlockSize = blockSize / sizeof(blockSize);
    const size_t bufferSize = sizeof(int);
    const string elementType = "int";

    long double elementTime = 0;
    vector<long double> timePointsWrite;
    vector<long double> timePointsRead;

    vector<int> dataBlock;
    string filename = "";

    if (memoryTypeIsRam(memoryType))
    {
        dataBlock.resize(blockSize, 0);
        elementTime = RAM_TIME;
    }
    else
    {
        if (memoryType == "SSD")
        {
            filename = (tempFilename == "" ? "/tmp/memorytest.bin" : tempFilename);
            elementTime = SSD_TIME;
        }
        else if (memoryType == "HDD")
        {
            filename = (tempFilename == "" ? "memorytest.bin" : tempFilename);
            elementTime = HDD_TIME;
        }
        else if (memoryType == "FLASH")
        {
            filename = (tempFilename == "" ? "memorytest.bin" : tempFilename);
            elementTime = FLASH_TIME;
        }
    }

    for (size_t i = 0; i < launchCount; i++)
    {
        timePointsWrite.push_back(testWrite(memoryType, dataBlockSize, dataBlock, filename));
        timePointsRead.push_back(testRead(memoryType, dataBlockSize, dataBlock, filename));
        if (filename != "")
        {
            remove(filename.c_str());
        }
    }

    const long double avgWriteTime = getAvgTimeFromVec(timePointsWrite);
    const long double avgReadTime = getAvgTimeFromVec(timePointsRead);
    const long double absErrorWrite = abs((elementTime * bufferSize * launchCount) - avgWriteTime);
    const long double absErrorRead = abs((elementTime * bufferSize * launchCount) - avgReadTime);
    const long double relErrorWrite = absErrorWrite / avgWriteTime * 100;
    const long double relErrorRead = absErrorRead / avgReadTime * 100;

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
    cout << fixed;

    const string timerType = "chrono::high_resolution_clock";
    string tempFilename = "";
    string memoryType = "RAM";
    vector<size_t> blockSizeCollection{1024};
    size_t launchCount = 10;
    bool isWriteToCsv = false;

    for (size_t i = 0; i < static_cast<size_t>(argc); i++)
    {
        if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--block-size"))
        {
            blockSizeCollection.clear();
            for (const auto &blockSize : split(argv[i + 1], ","))
            {
                blockSizeCollection.push_back(parseBlockSize(blockSize));
            }
        }
        if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--file-out"))
        {
            isWriteToCsv = true;
        }
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            cout
                << "-b SIZE, --block-size SIZE     Data block size in bytes. Default 1024. Use \",\" no spaces for enumeration, for example 1024,2048." << endl
                << "-f, --file-out                 Outputting data to a csv file. Filename is \"memory type\".csv." << endl
                << "-h, --help                     Help." << endl
                << "-l COUNT, --launch-count COUNT Number of tests performed. Default 10." << endl
                << "-m TYPE, --memory-type TYPE    The type of device for testing. May be RAM, SSD, HDD. Default RAM." << endl
                << "-t FILE, --temp-file FILE      Path to a temporary file that will be created at runtime for testing (excluding RAM memory type)." << endl;
            return EXIT_SUCCESS;
        }
        if (!strcmp(argv[i], "-l") || !strcmp(argv[i], "--launch-count"))
        {
            launchCount = atoll(argv[i + 1]);
        }
        if (!strcmp(argv[i], "-m") || !strcmp(argv[i], "--memory-type"))
        {
            memoryType = argv[i + 1];
        }
        if (!strcmp(argv[i], "-t") || !strcmp(argv[i], "--temp-file"))
        {
            tempFilename = argv[i + 1];
        }
    }

    if (memoryType == "RAM" || memoryType == "SSD" || memoryType == "HDD" || memoryType == "FLASH")
    {
        ofstream out;
        if (isWriteToCsv)
        {
            out.open(memoryType + ".csv", ios::out);
            if (!out.is_open())
            {
                cerr << "Unable to create output file." << endl;
                return EXIT_FAILURE;
            }
            std::cout.rdbuf(out.rdbuf());
        }

        printHeader();

        for (const auto &blockSize : blockSizeCollection)
        {
            doTest(timerType, memoryType, blockSize, launchCount, tempFilename);
        }

        if (out.is_open())
        {
            out.close();
        }
    }
    else
    {
        cerr << "Invalid input." << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}