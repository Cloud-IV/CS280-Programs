//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_3_Pt1_TestProgram.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "tokens.h"
#include "parse.h"

using namespace std;


int main(int argc, char *argv[])
{
    istream *in = &cin;                     //initializes pointer to point to standard input
    int lineNum = 0;
    ifstream inFile;

    if (argc == 2)                          //checks if one argument has been passed
    {
        inFile.open(argv[1]);               //attempts to open file listed using argument
        if (!inFile.is_open())              //prints error message if file fails to open and quits program
        {
            cerr << "COULD NOT OPEN " <<  argv[1] << "\n";
            return 0;
        }
        else in = &inFile;                  //if file successfully opens, changes in to point to inFile
    }
    else if (argc > 2)                      //checks if too many arguments were passed, prints error message, and quits
    {                                       //program
        cerr << "TOO MANY FILENAMES" << "\n";
        return 0;
    }

    ParseTree *prog = Prog(in, &lineNum);   //calls Prog constructor from parse.h that is defined in the parser
    if (prog == nullptr) return 0;          //checks if parse tree was able to be generated; if not, quits program

    return 0;
}
