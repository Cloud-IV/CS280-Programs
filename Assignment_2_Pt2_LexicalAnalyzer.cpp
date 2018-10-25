//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_2_Pt2_LexicalAnalyzer.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "tokens.h"

using namespace std;


Token
getNextToken(istream *in, int *linenum)
{
    enum LexState {INIT, IN_SCONST, IN_CMNT, IN_ERROR}; //lists valid states for finite state machine
    vector<char> operators = {'+', '-', '*', '/', '(', ')', ';', '=', '!', '>', '<', '&', '|'}; //valid operators
    LexState lexState = INIT;
    string lexeme;
    char c;

    while (in -> get(c))    //loops until no more characters can be retrieved from input
    {
        if (c == '\n') (*linenum)++;    //increments *linenum if new line is encountered
        switch (lexState)
        {
            case INIT:                  //initial state; handles switching to other states
                if (isspace(c)) continue;   //ignores whitespace
                lexeme = c;
                if (c == '"')           //checks c for string constant condition and switches case if needed
                {
                    lexState = IN_SCONST;
                    lexeme.clear();     //clears lexeme to get rid of double quote for if/when Token is printed
                    continue;
                }
                else if (find(operators.begin(), operators.end(), c) != operators.end())    //attempts to find c in operators
                {                                                                           //and returns the appropriate token
                    if (c == '+') return Token(PLUS, lexeme, *linenum);
                    else if (c == '-') return Token(MINUS, lexeme, *linenum);
                    else if (c == '*') return Token(STAR, lexeme, *linenum);
                    else if (c == '/') return Token(SLASH, lexeme, *linenum);
                    else if (c == '(') return Token(LPAREN, lexeme, *linenum);
                    else if (c == ')') return Token(RPAREN, lexeme, *linenum);
                    else if (c == ';') return Token(SC, lexeme, *linenum);
                    else if (c == '=') return Token(ASSIGN, lexeme, *linenum);
                    else if (c == '!') return Token(NEQ, lexeme, *linenum);
                    else if (c == '>') return Token(GT, lexeme, *linenum);
                    else if (c == '<') return Token(LT, lexeme, *linenum);
                    else if (c == '&') return Token(LOGICAND, lexeme, *linenum);
                    else if (c == '|') return Token(LOGICOR, lexeme, *linenum);
                }
                else if (c == '#')  //checks for comment condition and changes state if needed
                {
                    lexState = IN_CMNT;
                    continue;
                }
            case IN_SCONST:
                if (c == '\n')      //handles "new line in middle of string" error
                {
                    lexeme.insert(lexeme.begin(), '"'); //reinserts double quote at beginning for error message
                    lexState = IN_ERROR;
                }
                else if (c == '"') return Token(SCONST, lexeme, *linenum);  //returns Token upon encountering second double quote
                lexeme += c;        //adds current char to lexeme
                continue;
            case IN_CMNT:
                if (c == '\n') lexState = INIT; //if newline is encountered, changes state back to INIT
                continue;
            case IN_ERROR:
                return Token(ERR, lexeme, *linenum);    //handles ERR tokens
        }
    }
    return Token(DONE, lexeme, *linenum);   //once no more chars can be retrieved, returns DONE token
}