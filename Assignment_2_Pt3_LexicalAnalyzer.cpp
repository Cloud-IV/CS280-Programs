//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_2_Pt3_LexicalAnalyzer.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "tokens.h"

using namespace std;


vector<char> operators = {'+', '-', '*', '/', '(', ')', ';', '=', '!', '>', '<', '&', '|'}; //valid operators
bool isOperator(char c)                                                                 //method that tests if c is an operator
{
    if (find(operators.begin(), operators.end(), c) != operators.end()) return true;
    else return false;
}

Token
getNextToken(istream *in, int *linenum)
{
    enum LexState {INIT, IN_IDENT, IN_ICONST, IN_SCONST, IN_OPRTR, IN_CMNT, IN_ERROR}; //lists valid states for finite state machine
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
                if (c == '.')           //if initial char is a period, changes lexState to IN_ERROR
                {
                    lexState = IN_ERROR;
                    continue;
                }
                else if (isalpha(c))
                {
                    lexState = IN_IDENT;
                    continue;
                }
                else if (isdigit(c))
                {
                    lexState = IN_ICONST;
                    continue;
                }
                else if (c == '"')
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
                    else if (c == '=' || c == '!' || c == '>' || c == '<' || c == '&' || c == '|') //changes state to check for
                    {                                                                              //double char operators if applicable
                        lexState = IN_OPRTR;
                        continue;
                    }
                }
                else if (c == '#')
                {
                    lexState = IN_CMNT;
                    continue;
                }
            case IN_IDENT:
                if (isalpha(c) || isdigit(c))   //continues adding c to lexeme as long as c is a letter or digit
                {
                    lexeme += c;
                    continue;
                }
                else if (isOperator(c)) //checks if identifier is followed immediately by an operator
                {
                    in -> putback(c);
                    if (lexeme == "print") return Token(PRINT, lexeme, *linenum);   //checks if current lexeme is a keyword
                    else if (lexeme == "if") return Token(IF, lexeme, *linenum);
                    else if (lexeme == "then") return Token(THEN, lexeme, *linenum);
                    else if (lexeme == "true") return Token(TRUE, lexeme, *linenum);
                    else if (lexeme == "false") return Token(FALSE, lexeme, *linenum);
                    else return Token(IDENT, lexeme, *linenum);
                }
                else if (c == '"' || c == '\'' || c == '.') //checks if identifier is immediately followed by punctuation
                {
                    in -> putback(c);
                    return Token(IDENT, lexeme, *linenum);
                }
                if (lexeme == "print") return Token(PRINT, lexeme, *linenum);   //checks if current lexeme is keyword given
                else if (lexeme == "if") return Token(IF, lexeme, *linenum);    //above conditions fail
                else if (lexeme == "then") return Token(THEN, lexeme, *linenum);
                else if (lexeme == "true") return Token(TRUE, lexeme, *linenum);
                else if (lexeme == "false") return Token(FALSE, lexeme, *linenum);
                else return Token(IDENT, lexeme, *linenum);
            case IN_ICONST:
                if (isdigit(c))     //continues adding c to lexeme as long as c is a digit
                {
                    lexeme += c;
                    continue;
                }
                else if (c == '"' || c == '\'' || c == '.')  //checks if integer constant is interrupted by punctuation
                {
                    in -> putback(c);
                    return Token(ICONST, lexeme, *linenum);
                }
                else if (isalpha(c))    //if c is a letter, changes lexState to IN_ERROR
                {
                    in -> putback(c);
                    lexState = IN_ERROR;
                }
                else if (isspace(c)) return Token(ICONST, lexeme, *linenum);    //checks for spaces that delimit tokens
                else if (isOperator(c))     //checks if char immediately following integer constant is an operator
                {
                    in -> putback(c);
                    return Token(ICONST, lexeme, *linenum);
                }
            case IN_SCONST:
                if (c == '\n')      //handles "new line in middle of string" error
                {
                    lexeme.insert(lexeme.begin(), '"'); //reinserts double quote at beginning for error message
                    lexeme += c;
                    return Token(ERR, lexeme, *linenum);
                }
                else if (c == '"') return Token(SCONST, lexeme, *linenum);  //returns Token upon encountering second double quote
                else
                    {
                        lexeme += c;        //adds current char to lexeme
                        continue;
                    }
            case IN_OPRTR:
                if (c == '\n')              //checks if second char in double char operator is newline
                {
                    lexState = IN_ERROR;
                    continue;
                }
                else if (c != '=' && c != '&' && c != '|')  //checks if second char in double char operator is a valid operator
                {
                    in -> putback(c);                                           //if not valid, handles single char operator
                    if (lexeme == "=") return Token(ASSIGN, lexeme, *linenum);
                    else if (lexeme == ">") return Token(GT, lexeme, *linenum);
                    else if (lexeme == "<") return Token(LT, lexeme, *linenum);
                }
                else if (lexeme == "=" && c == '=')     //checks for each possible double char operator combination
                {
                    lexeme += c;
                    return Token(EQ, lexeme, *linenum);
                }
                else if (lexeme == "!" && c == '=')
                {
                    lexeme += c;
                    return Token(NEQ, lexeme, *linenum);
                }
                else if (lexeme == ">" && c == '=')
                {
                    lexeme += c;
                    return Token(GEQ, lexeme, *linenum);
                }
                else if (lexeme == "<" && c == '=')
                {
                    lexeme += c;
                    return Token(LEQ, lexeme, *linenum);
                }
                else if (lexeme == "&" && c == '&')
                {
                    lexeme += c;
                    return Token(LOGICAND, lexeme, *linenum);
                }
                else if (lexeme == "|" && c == '|')
                {
                    lexeme += c;
                    return Token(LOGICOR, lexeme, *linenum);
                }
            case IN_CMNT:
                if (c == '\n') lexState = INIT; //if newline is encountered, changes state back to INIT
                continue;
            case IN_ERROR:
                return Token(ERR, lexeme, *linenum);    //handles ERR tokens
        }
    }
    return Token(DONE, lexeme, *linenum);   //once no more chars can be retrieved, returns DONE token
}
