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
    string lineIn;

    while (true)
    {
        getline(cin, lineIn);

        vector<string> args = split(lineIn, " ");

        if (args.size() > 0 && args[0] != "")
        {
            string linuxCommand = args[0];
            string commandToExecute("");

            if (linuxCommand == "touch")
            {
                commandToExecute = "type NUL > " + args[1];
            }
            else if (linuxCommand == "cat")
            {
                commandToExecute = "type " + args[1];
            }
            else if (linuxCommand == "mkdir")
            {
                commandToExecute = lineIn;
            }
            else if (linuxCommand == "pkill")
            {
                commandToExecute = "taskkill /IM " + args[1];
            }
            else if (linuxCommand == "clear")
            {
                commandToExecute = "cls";
            }
            else if (linuxCommand == "whoami")
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
            else if (linuxCommand == "hostname")
            {
                commandToExecute = lineIn;
            }
            else if (linuxCommand == "exit")
            {
                exit(EXIT_SUCCESS);
            }
            else
            {
                commandToExecute = lineIn;
            }

            system(commandToExecute.c_str());
        }
    }

    return EXIT_SUCCESS;
}