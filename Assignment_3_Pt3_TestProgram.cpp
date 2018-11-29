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

    else                                    //handles output generation if parse tree was successfully generated
    {
        cout << "LEAF COUNT: " << prog -> leafCount() << "\n";
        cout << "STRING COUNT: " << prog -> stringCount(&ParseTree::isString) << "\n";
        int identCount = prog -> identCount(&ParseTree::isIdent);
        if (identCount != 0)                //checks if any identifiers were found
        {
            cout << "IDENT COUNT: " << identCount << "\n";
            istringstream is(prog -> identFreq(&ParseTree::getID)); //pushes return string from identFreq into a stringstream
            vector<string> idVec;           //will hold all identifiers from is
            map<string, int> idMap;         //will hold identifiers and their times encountered
            map<int, vector<string>> idFreq;//will hold the swapped values of idMap, accounting for repeated values
            map<string, int>::iterator mi;
            map<int, vector<string>>::iterator fi;
            string ID;
            while (is >> ID) idVec.push_back(ID);   //is automatically tokenizes string from identFreq and adds them to idVec
            for (string &s : idVec) idMap[s]++;     //populates idMap with strings and times encountered
            for (mi = idMap.begin(); mi != idMap.end(); mi++) idFreq[mi -> second].push_back(mi -> first);  //swaps keys and values from idMap into idFreq
            cout << idFreq.rbegin() -> second[0];   //prints first identifier for the last key, which is the most frequent id
            for (int i = 1; i < idFreq.rbegin() -> second.size(); i++) cout << ", " << idFreq.rbegin() -> second[i]; //prints out any additional most frequent ids
            cout << "\n";
        }
    }
    return 0;
}
