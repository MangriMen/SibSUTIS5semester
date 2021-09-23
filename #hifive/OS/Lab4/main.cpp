#include <iostream>
#include <vector>
using namespace std;

int main()
{
    string inna = "";

    while (true)
    {
        cin >> inna;

        vector<string> saske;

        if (inna == "touch")
        {
            // NUL >./
        }
        else if (inna == "mv")
        {
            system("copy args[1] args[2]");
            system("del /f args[1]");
        }
    }

    return EXIT_SUCCESS;
}