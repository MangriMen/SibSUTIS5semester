#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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
        getline(cin, in);

        vector<string> args = split(in, " ");

        if (args.size() > 0 && args[0] != "")
        {
            string com_ = args[0];
            string execCommand("");
            if (com_ == "touch")
            {
                execCommand = "type NUL > " + args[1];
            }
            else if (com_ == "cat")
            {
                execCommand = "type " + args[1];
            }
            else if (com_ == "mkdir")
            {
                execCommand = in;
            }
            else if (com_ == "kill")
            {
                for (size_t i = 1; i < args.size(); i++)
                {
                    execCommand = "taskkill /PID " + args[i];
                }
            }
            else if (com_ == "pkill")
            {
                for (size_t i = 1; i < args.size(); i++)
                {
                    execCommand = "taskkill /IM " + args[i] + " ";
                }
            }
            else if (com_ == "clear")
            {
                execCommand = "cls";
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
                execCommand = in;
            }
            else if (com_ == "exit")
            {
                exit(EXIT_SUCCESS);
            }
            else
            {
                execCommand = in;
            }
            cout << execCommand;
            system(execCommand.c_str());
        }
    }
    return EXIT_SUCCESS;
}