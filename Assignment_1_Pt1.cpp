//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_1_Pt1.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

int main(int argc, char *argv[])
{
    if (argv[1] == nullptr)                                     //checks if N exists
    {
        cout << "NO PHRASE LENGTH\n";
        return 0;
    }
    else if (*argv[1] < 0 || strtol(argv[1], nullptr, 0) == 0)  //checks if N is less than 0 or is not an integer by
    {                                                           //attempting to convert to an integer using strtol (if
        cout << "INVALID PHRASE LENGTH\n";                      //strtol fails, then it returns 0)
        return 0;
    }
    else if (argv[2] == nullptr)                                //checks if second argument exists
    {
        cout << "NO MODE";
        return 0;
    }
    else if (strcmp(argv[2], "all") != 0 && strcmp(argv[2], "top") != 0)  // checks if second argument is "all" or "top"
    {
        cout << "INVALID MODE\n";
        return 0;
    }
    else if (argv[3] == nullptr)                                //checks if a file name exists
    {
        cout << "NO FILES GIVEN\n";
        return 0;
    }
    for (int i = 3; i < argc; i++)                              //iterates through file names and checks to see if one
    {                                                           //is invalid
        ifstream inFile;
        inFile.open(argv[i]);
        if (!inFile.is_open())
        {
            cout << "BAD FILE " << argv[i] << "\n";
            return 0;
        }
    }
}
