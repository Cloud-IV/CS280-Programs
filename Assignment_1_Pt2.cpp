//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_1_Pt2.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <map>
#include <locale>

using namespace std;

int main(int argc, char *argv[])
{
    if (argv[1] == nullptr)                                     //checks if N exists
    {
        cerr << "NO PHRASE LENGTH\n";
        return 0;
    }
    else if (*argv[1] <= 0 || strtol(argv[1], nullptr, 0) == 0) //checks if N is less than or equal to 0 or is not an integer by
    {                                                           //attempting to convert to an integer using strtol (if
        cerr << "INVALID PHRASE LENGTH\n";                      //strtol fails, then it returns 0)
        return 0;
    }
    else if (argv[2] == nullptr)                                //checks if second argument exists
    {
        cerr << "NO MODE";
        return 0;
    }
    else if (strcmp(argv[2], "all") != 0 && strcmp(argv[2], "top") != 0)  // checks if second argument is "all" or "top"
    {
        cerr << "INVALID MODE\n";
        return 0;
    }
    else if (argv[3] == nullptr)                                //checks if a file name exists
    {
        cerr << "NO FILES GIVEN\n";
        return 0;
    }
    for (int i = 3; i < argc; i++)                              //iterates through file names and checks to see if one
    {                                                           //is invalid.
        ifstream inFile;                                        //file variable creation
        inFile.open(argv[i]);                                   //opens current file based on name in argv[i]
        if (!inFile.is_open())                                  //checks if file was successfully opened
        {
            cerr << "BAD FILE " << argv[i] << "\n";
            return 0;
        }
        string word;                                            //word to be read in from string stream
        ostringstream os;                                       //string stream variable
        locale loc;                                             //locale variable for use in tolower(char, locale)
        map<string, int> countMap;                              //map creation to store how many times a string has been seen
        int phraseLen = strtol(argv[1], nullptr, 0);            //initializes phrase length variable
        int wordCounter = 0;                                    //word counter to keep track of how many words in current phrase
        while (inFile >> word && wordCounter < phraseLen)       //checks that there is a word in inFile and that the
        {                                                       //phrase length has not been reached.
            string lowerWord;                                   //variable to store lower case version of word
            for (char c : word) lowerWord += tolower(c, loc);   //converts each char in word to lowercase
            os << lowerWord << " ";                             //pushes the converted word to the outward string stream
            wordCounter++;                                      //increments word counter
            if (wordCounter == phraseLen)                       //checks if word counter has reached phrase length
            {
                string phrase = os.str();                       //combines words in os into one string
                if (countMap.find(phrase) == countMap.end()) countMap[phrase]++;    //checks if phrase exists in map; if not, creates entry
                else countMap[phrase]++;                        //if entry exists, increment integer value
                os.str("");                                     //clears os stream
                wordCounter = 0;                                //resets word counter to 0 so next phrase can be found
            }
        }
        if (countMap.empty())                                   //checks if map is empty
        {
            cerr << "NO PHRASES\n";
            return 0;
        }
        map<string, int>::iterator mi;
        if (string(argv[2]) == "all")                           //checks if mode is "all"
        {                                                       //iterates through map and prints out phrase keys and their times seen
            for (mi = countMap.begin(); mi != countMap.end(); mi++) cout << mi->first << mi->second << "\n";
        }
    }
    return 0;
}
