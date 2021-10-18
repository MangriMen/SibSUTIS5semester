#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <process.h>

using namespace std;

vector<string> split(string phrase, string delimiter)
{
    vector<string> list;
    string s = string(phrase);
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos)
    {
        token = s.substr(0, pos);
        list.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(s);
    return list;
}

int main()
{
    string in;
    while (true)
    {
        getline(cin, in, '\n');

        vector<string> args = split(in, " ");
        size_t argc_ = args.size() + 3;

        char **argsCh = new char *[argc_];
        argsCh[0] = new char[4];
        argsCh[1] = new char[3];
        sprintf(argsCh[0], "cmd");
        sprintf(argsCh[1], "/C");
        for (size_t i = 2; i < argc_; i++)
        {
            argsCh[i] = new char[args[i].size() + 1];
            sprintf(argsCh[i], "%s", args[i].c_str());
        }
        argsCh[argc_ - 1] = NULL;

        for (size_t i = 0; i < argc_; i++)
        {
            cout << argsCh[i];
        }

        cout << endl;
        if (args.size() > 0 && args[0] != "")
        {
            string com_ = args[0];
            if (com_ == "touch")
            {
                argsCh[0] = "type NUL >\0";
                _spawnvp(P_WAIT, "cmd", argsCh);
            }
            else if (com_ == "cat")
            {
                _spawnvp(P_WAIT, "cmd /C", argsCh);
            }
            else if (com_ == "mkdir")
            {
                _spawnvp(P_WAIT, argsCh[0], argsCh);
            }
            else if (com_ == "kill")
            {
                for (size_t i = 1; i < args.size(); i++)
                {
                    // execCommand = "taskkill /PID " + args[i];
                }
            }
            else if (com_ == "pkill")
            {
                for (size_t i = 1; i < args.size(); i++)
                {
                    // execCommand = "taskkill /IM " + args[i] + " ";
                }
            }
            else if (com_ == "clear")
            {
                // execCommand = "cls";
            }
            else if (com_ == "whoami")
            {
                system("whoami > temp");
                ifstream fileIn("temp", ios::in);
                string tmpStr("");
                if (fileIn.is_open())
                {
                    fileIn >> tmpStr;
                }
                vector<string> output = split(tmpStr, "\\");
                cout << output[1] << endl;
                continue;
            }
            else if (com_ == "hostname")
            {
                char *test[] = {"cmd", "/C", "hostname", NULL};
                _spawnvp(P_WAIT, argsCh[0], argsCh);
            }
            else if (com_ == "exit")
            {
                exit(EXIT_SUCCESS);
            }
        }
    }
    return EXIT_SUCCESS;
}