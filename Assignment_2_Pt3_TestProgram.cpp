//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_2_Pt3_TestProgram.cpp
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
    if (tt == IDENT) return out << "IDENT(" << tok.GetLexeme() << ")";
    else if (tt == ICONST) return out << "ICONST(" << tok.GetLexeme() << ")";
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
    else return out << "UNABLE TO PRINT TOKEN"; //for debugging purposes; should never print unless an error occurs
}


int main(int argc, char *argv[])
{
    vector<string> validFlag = {"-v", "-sum", "-allids"};       //vector containing all valid flags
    bool verboseFlag = false;                                   //bool flag to keep track of verbose mode
    bool allID_Flag = false;                                    //keeps track of all id mode
    bool sumFlag = false;                                       //keeps track of sum mode
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
        if (strcmp(argv[i], "-allids") == 0) allID_Flag = true; //checks for -allids arg and changes flag accordingly
        if (strcmp(argv[i], "-sum") == 0) sumFlag = true;       //checks for -sum arg and changes flag accordingly
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
    if (!verboseFlag && !allID_Flag && !sumFlag) return 0;

    int lineNum = 0;                                            //keeps track of current line number
    int tokenCount = 0;                                         //keeps track of Tokens for -sum mode
    int idCount = 0;                                            //keeps track of identifiers for -sum mode
    int stringCount = 0;                                        //keeps track of strings for -sum mode
    vector<string> ids;                                         //vector to store encountered identifiers for -allids mode
    vector<string>::iterator vi;
    Token tk;
    while ((tk = getNextToken(in, &lineNum)) != DONE && tk != ERR)
    {
        if (verboseFlag) cout << tk << "\n";                    //checks if -v was passed as an arg and handles verbose mode
        tokenCount++;
        if (tk == IDENT)                                        //if tk is an identifier, increments idCount and adds tk's lexeme
        {                                                       //to ids vector if not already encountered
            idCount++;
            if (find(ids.begin(), ids.end(), tk.GetLexeme()) == ids.end()) ids.push_back(tk.GetLexeme());
        }
        if (tk == SCONST) stringCount++;
    }
    if (tk == ERR) cout << tk << "\n";                          //handles error messages
    else if (allID_Flag && !ids.empty())                        //handles -allids mode
    {
        cout << "IDENTIFIERS: ";
        sort(ids.begin(), ids.end());
        cout << ids[0];
        for (vi = ids.begin() + 1; vi != ids.end(); vi++) cout << ", " <<*vi;
        cout << "\n";
    }
    if (sumFlag)                                                //handles -sum mode
    {
        cout << "Total lines: " << tk.GetLinenum() << "\n",
        cout << "Total tokens: " << tokenCount << "\n";
        cout << "Total identifiers: " << idCount << "\n";
        cout << "Total strings: " << stringCount << "\n";
    }
}
