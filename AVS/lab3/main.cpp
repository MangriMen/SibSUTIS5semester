#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <map>
#include <any>
#include <tuple>
#include <variant>
#include <climits>
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
#include <cxxabi.h>
#endif

using namespace std;

#define NANO 10e9
constexpr long double RAM_TIME = 0.0000000000205374;
constexpr long double SSD_WRITE_TIME = 0.0000000018662902;
constexpr long double SSD_READ_TIME = 0.0000000029434392;
constexpr long double HDD_WRITE_TIME = 520 / 10e8;
constexpr long double HDD_READ_TIME = 520 / 10e8;
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

template <typename T>
long double testWriteRead(string memoryType, size_t dataBlockSize, const ios_base::openmode mode, string filename = "")
{
    auto localStart = chrono::high_resolution_clock::now();
    auto localStop = chrono::high_resolution_clock::now();

    random_device rd;
    mt19937_64 randEngine(rd());
    uniform_int_distribution<unsigned long long> distr(0, static_cast<unsigned long long>(pow(2, sizeof(T) * CHAR_BIT)));

    fstream file;
    file.rdbuf()->pubsetbuf(0, 0);
    ios_base::openmode flags = mode | ios::binary;
    if (!(memoryType == "RAM"))
    {
        file.open(filename, flags);
        if (!file.is_open())
        {
            return -EXIT_FAILURE;
        }
    }

    T *tempData = new T[dataBlockSize];
    for (size_t i = 0; i < dataBlockSize; i++)
    {
        tempData[i] = i;
        // tempData[i] = distr(randEngine);
    }
    char *tempDataPChar = reinterpret_cast<char *>(tempData);
    size_t blockSize = dataBlockSize * sizeof(T);

    long double allElapsedTime = 0;

    if (memoryType == "RAM")
    {
        T *tempMemoryBlock = new T[dataBlockSize];
        // for (size_t i = 0; i < dataBlockSize; i++)
        // {
        //     localStart = chrono::high_resolution_clock::now();
        //     // tempMemoryBlock[i] = tempData[i];
        //     localStop = chrono::high_resolution_clock::now();
        //     allElapsedTime += chrono::duration<long double>(localStop - localStart).count();
        // }
        localStart = chrono::high_resolution_clock::now();
        memcpy(tempMemoryBlock, tempData, dataBlockSize * sizeof(T));
        localStop = chrono::high_resolution_clock::now();
        // memcpy_s(tempMemoryBlock, dataBlockSize * sizeof(T), tempData, dataBlockSize * sizeof(T));
        allElapsedTime = chrono::duration<long double>(localStop - localStart).count();
        delete[] tempMemoryBlock;
    }
    else
    {
        if (mode == ios::out)
        {
            localStart = chrono::high_resolution_clock::now();
            file.write(tempDataPChar, blockSize);
            localStop = chrono::high_resolution_clock::now();
        }
        else if (mode == ios::in)
        {
            localStart = chrono::high_resolution_clock::now();
            file.read(tempDataPChar, blockSize);
            localStop = chrono::high_resolution_clock::now();
        }

        allElapsedTime = chrono::duration<long double>(localStop - localStart).count();
        file.close();
    }

    delete[] tempData;

    return allElapsedTime;
}

template <typename T>
long double testWrite(const string memoryType, const size_t dataBlockSize, string filename = "")
{
    return testWriteRead<T>(memoryType, dataBlockSize, ios::out, filename);
}

template <typename T>
long double testRead(const string memoryType, const size_t dataBlockSize, string filename = "")
{
    return testWriteRead<T>(memoryType, dataBlockSize, ios::in, filename);
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

template <typename T>
void testMemory(const string timerType, const string memoryType, const size_t blockSize, const size_t launchCount, const string tempFilename = "")
{
    const size_t dataBlockSize = blockSize / sizeof(T);
    const size_t bufferSize = sizeof(T);
    int status = 0;
#if defined(__GNUC__) || defined(__MINGW32__) || defined(__MINGW64__)
    const string elementType = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
#else
    const string elementType = typeid(T).name();
#endif

    long double elementWriteTime = 0;
    long double elementReadTime = 0;
    vector<long double> timePointsWrite;
    vector<long double> timePointsRead;

    string filename = "";

    if (memoryType == "RAM")
    {
        elementWriteTime = RAM_TIME;
        elementReadTime = RAM_TIME;
    }
    else
    {
        if (memoryType == "SSD")
        {
            filename = (tempFilename == "" ? "/tmp/memorytest.bin" : tempFilename);
            elementWriteTime = SSD_WRITE_TIME;
            elementReadTime = SSD_READ_TIME;
        }
        else if (memoryType == "HDD")
        {
            filename = (tempFilename == "" ? "memorytest.bin" : tempFilename);
            elementWriteTime = HDD_WRITE_TIME;
            elementReadTime = HDD_READ_TIME;
        }
        else if (memoryType == "FLASH")
        {
            filename = (tempFilename == "" ? "memorytest.bin" : tempFilename);
            elementWriteTime = FLASH_TIME;
            elementReadTime = FLASH_TIME;
        }
    }

    for (size_t i = 0; i < launchCount; i++)
    {
        timePointsWrite.push_back(testWrite<T>(memoryType, dataBlockSize, filename));
        timePointsRead.push_back(testRead<T>(memoryType, dataBlockSize, filename));
        // if (filename != "")
        // {
        //     remove(filename.c_str());
        // }
    }

    const long double avgWriteTime = getAvgTimeFromVec(timePointsWrite);
    const long double avgReadTime = getAvgTimeFromVec(timePointsRead);
    const long double absErrorWrite = abs((elementWriteTime * bufferSize) - (avgWriteTime / blockSize));
    const long double absErrorRead = abs((elementReadTime * bufferSize) - (avgReadTime / blockSize));
    const long double relErrorWrite = absErrorWrite / avgWriteTime * 100;
    const long double relErrorRead = absErrorRead / avgReadTime * 100;

    for (size_t i = 0; i < launchCount; i++)
    {
        const long double writeBandwidth = (blockSize / avgWriteTime) / 1024 / 1024;
        const long double readBandwidth = (blockSize / avgReadTime) / 1024 / 1024;

        cout << memoryType << ";"
             << blockSize << ";"
             << elementType << ";"
             << bufferSize << ";"
             << i + 1 << ";"
             << timerType << ";"
             << timePointsWrite[i] << ";"
             << avgWriteTime << ";"
             << writeBandwidth << ";"
             << absErrorWrite << ";"
             << relErrorWrite << "%;"
             << timePointsRead[i] << ";"
             << avgReadTime << ";"
             << readBandwidth << ";"
             << absErrorRead << ";"
             << relErrorRead << "%"
             << endl;
    }
}

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int>(time(NULL)));

    cout.imbue(std::locale(std::locale::classic(), new Comma));
    cout << fixed << setprecision(16);

    const string timerType = "chrono::high_resolution_clock";
    string tempFilename = "";
    string memoryType = "RAM";
    vector<size_t> blockSizeCollection{1024};
    vector<string> dataTypeCollection{"int"};
    size_t launchCount = 10;
    bool isWriteToCsv = false;

    for (size_t i = 0; i < static_cast<size_t>(argc); i++)
    {
        if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--block-size"))
        {
            blockSizeCollection.clear();
            vector<string> blockSizes = split(argv[i + 1], ",");
            for (const auto &blockSize : blockSizes)
            {
                blockSizeCollection.push_back(parseBlockSize(blockSize));
            }
        }
        if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--data-type"))
        {
            dataTypeCollection.clear();
            dataTypeCollection = split(argv[i + 1], ",");
            for (auto &dataType : dataTypeCollection)
            {
                transform(dataType.begin(), dataType.end(), dataType.begin(), ::tolower);
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
                << "-d TYPE, --data-type"
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
            for (const auto &dataType : dataTypeCollection)
            {
                if (dataType == "char")
                {
                    testMemory<unsigned char>(timerType, memoryType, blockSize, launchCount, tempFilename);
                }
                else if (dataType == "short")
                {
                    testMemory<unsigned short>(timerType, memoryType, blockSize, launchCount, tempFilename);
                }
                else if (dataType == "int")
                {
                    testMemory<unsigned int>(timerType, memoryType, blockSize, launchCount, tempFilename);
                }
                else if (dataType == "long long" || dataType == "llong")
                {
                    testMemory<unsigned long long>(timerType, memoryType, blockSize, launchCount, tempFilename);
                }
            }
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