//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_2_Pt1_TestProgram.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include "tokens.h"

using namespace std;


int main(int argc, char *argv[])
{
    vector<string> validFlag = {"-v", "-sum", "-allids"};       //vector containing all valid flags
    int fileCount = 0;                                          //count how many filenames are encountered during loop

    for (int i = 1; i < argc; i++)                              //iterates over arguments
    {
        if ((argv[i][0] == '-') && (find(validFlag.begin(), validFlag.end(), argv[i]) == validFlag.end())) //checks
        {                                                       //first char for dash and searches for arg in validFlag.
            cerr << "INVALID FLAG" << " " << argv[i] << "\n";   //if arg has a dash but not in validFlag, prints err msg
            return 0;
        }
        if (argv[i][0] != '-') fileCount++;                     //increments fileCount if arg with no dash encountered
        if (fileCount > 1)                                      //if fileCount > 1, prints err msg
        {
            cerr << "TOO MANY FILE NAMES" << "\n";
            return 0;
        }
    }
    if (argv[argc - 1][0] != '-')                               //checks if last arg is a flag
    {
        ifstream inFile;
        inFile.open(argv[argc - 1]);                            //opens file with name of last arg
        if (!inFile.is_open())                                  //checks if file was successfully opened
        {
            cerr << "UNABLE TO OPEN " << argv[argc - 1] << "\n";    //if file is not open, prints err msg
            return 0;
        }
    }
}