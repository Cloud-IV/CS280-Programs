//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_2_Pt1_TestProgram.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include "tokens.h"

using namespace std;


ostream& operator<<(ostream& out, const Token& tok) //overloads << for Tokens so they can be printed out
{
    TokenType tt = tok.GetTokenType();
    if (tt == IDENT) return out << "IDENT (" << tok.GetLexeme() << ")";
    else if (tt == ICONST) return out << "ICONST (" << tok.GetLexeme() << ")";
    else if (tt == SCONST) return out << "SCONST(" << tok.GetLexeme() << ")";
    else if (tt == PRINT) return out << "PRINT";
    else if (tt == IF) return out << "IF";
    else if (tt == THEN) return out << "THEN";
    else if (tt == TRUE) return out << "TRUE";
    else if (tt == FALSE) return out << "FALSE";
    else if (tt == PLUS) return out << "PLUS";
    else if (tt == MINUS) return out << "MINUS";
    else if (tt == STAR) return out << "STAR";
    else if (tt == SLASH) return out << "SLASH";
    else if (tt == ASSIGN) return out << "ASSIGN";
    else if (tt == EQ) return out << "EQ";
    else if (tt == NEQ) return out << "NEQ";
    else if (tt == LT) return out << "LT";
    else if (tt == LEQ) return out << "LEQ";
    else if (tt == GT) return out << "GT";
    else if (tt == GEQ) return out << "GEQ";
    else if (tt == LOGICAND) return out << "LOGICAND";
    else if (tt == LOGICOR) return out << "LOGICOR";
    else if (tt == LPAREN) return out << "LPAREN";
    else if (tt == RPAREN) return out << "RPAREN";
    else if (tt == SC) return out << "SC";
    else if (tt == ERR) return out << "Error on line " << tok.GetLinenum() << " " << "(" << tok.GetLexeme() << ")";
    else return out << "UNABLE TO PRINT TOKEN";
}


int main(int argc, char *argv[])
{
    vector<string> validFlag = {"-v", "-sum", "-allids"};       //vector containing all valid flags
    bool verboseFlag = false;                                   //bool flag to keep track of verbose mode
    istream *in = &cin;                                         //default init of in to point to standard input
    int fileCount = 0;                                          //count how many file names are encountered during loop
    ifstream inFile;                                            //file to be read from, if necessary

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
        if (strcmp(argv[i], "-v") == 0) verboseFlag = true;     //checks if -v arg was passed and changes flag accordingly
    }
    if (argv[argc - 1][0] != '-')                               //checks if last arg is a flag
    {
        inFile.open(argv[argc - 1]);                            //opens file with name of last arg
        if (!inFile.is_open())                                  //checks if file was successfully opened
        {
            cerr << "UNABLE TO OPEN " << argv[argc - 1] << "\n";    //if file is not open, prints err msg
            return 0;
        }
        else in = &inFile;                                      //changes in to point to inFile
    }

    int lineNum = 0;                                            //keeps track of current line number
    Token tk;
    while ((tk = getNextToken(in, &lineNum)) != DONE && tk != ERR)
    {
        if (verboseFlag) cout << tk << "\n";                    //checks if -v was passed as an arg and handles verbose mode
        else return 0;                                          //exits program if no args were passed
    }
    if (tk == ERR) cout << tk << "\n";                          //handles error messages
}