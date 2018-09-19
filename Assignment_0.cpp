//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_0.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    if (argv[1] != nullptr)                         //checks if first argument exists
    {
        for (int i = 1; i < argc; i++)              //iterates through arguments
        {
            int argLen(string(argv[i]).length());   //length of the current argument in the loop
            char firstChar = argv[i][0];            //the first letter of the current argument

            if (firstChar == 'S') continue;         //if the first char is "S", continue looping
            else if (firstChar == 'L')              //if first char is "L", change uppercase letters to lowercase
            {
                for (int j = 1; j < argLen; j++)    //loops through letters of current argument
                    putchar(tolower(argv[i][j]));   //converts each char to lowercase, if applicable, then prints chars
                cout << "\n";
            }
            else if (firstChar == 'U')
            {
                for (int j = 1; j < argLen; j++)    //loops through letters of current argument
                    putchar(toupper(argv[i][j]));   //converts each char to uppercase, if applicable, then prints chars
                cout << "\n";
            }
            else if (firstChar == 'r')
            {
                for (int j = (argLen - 1); j > 0; j--)  //loops through letters of current argument, but in reverse
                    putchar(argv[i][j]);            //prints chars in reverse order
                cout << "\n";
            }
            else if (firstChar == 'R')
            {
                for (int j = (argLen - 1); j > 0; j--)  //loops through letters of current argument, but in reverse
                    putchar(toupper(argv[i][j]));   //prints chars in reverse order after converting to uppercase
                cout << "\n";
            }
            else cout << "FAIL\n";
        }
    }
    return 0;
}