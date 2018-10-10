//----------------------------------------------------------------------------------------------------------------------
// Author: Abrar Rouf
// Assignment_1_Pt3.cpp
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <vector>
#include <map>
#include <locale>
#include <algorithm>

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
    string word;                                                //used to read in words from files
    string lowerWord;                                           //used to store converted lowercase words
    string phrase;                                              //stores string that makes up phrase
    ifstream inFile;
    locale loc;                                                 //used in tolower() for lowercase conversion
    vector<string> fileVector;                                  //holds vector of lowercase strings
    vector<string> phraseVector;                                //holds strings that make up phrase
    vector<map<string, int>> mapVec;                            //vector that holds maps for frequency across all files
    map<string, int> countMap;                                  //map for just one file for frequency of words
    int phraseLen = strtol(argv[1], nullptr, 0);
    for (int i = 3; i < argc; i++)                              //iterates through file names and checks to see if one
    {                                                           //is invalid.
        inFile.open(argv[i]);                                   //opens current file based on name in argv[i]
        if (!inFile.is_open())                                  //checks if file was successfully opened
        {
            cerr << "BAD FILE " << argv[i] << "\n";
            return 0;
        }
        while (inFile >> word)                                  //reads in words
        {
            for (char c : word) lowerWord += tolower(c, loc);   //converts chars of words to lowercase
            fileVector.push_back(lowerWord);                    //adds converted word to vector
            lowerWord = "";                                     //clears lowerWord so a new word can be converted
        }
        inFile.close();
        int phraseStart = 0;                                    //used to mark beginning of phrase in fileVector
        int phraseEnd = phraseStart + (phraseLen - 1);          //denotes end of phrase in fileVector
        while (phraseEnd < fileVector.size())
        {
            phrase = fileVector[phraseStart];                   //initializes phrase to be the first word in fileVector
            for (int j = phraseStart + 1; j < phraseEnd + 1; j++) //iterates through words in fileVector, bounded by phraseStart/End
            {
                phrase += " " + fileVector[j];          //appends each word to phrase
            }
            phraseVector.push_back(phrase);             //adds entire phrase into vector
            phraseStart++;                              //increments phraseStart so it points to the next word in fileVector
            phraseEnd++;                                //increments phraseEnd so the phrase length remains unchanged
        }
        for (string& s : phraseVector) countMap[s]++;   //creates entries for phrases in countMap along with their frequencies
        mapVec.push_back(countMap);                     //adds entire map to mapVec
        countMap.clear();                               //clears countMap so next file can use it
        phraseVector.clear();                           //clears phraseVector for next file
        fileVector.clear();                             //clears fileVector for next file
    }
    map<string, int> fnlMap;                            //map used to hold frequencies for phrases across all maps
    for (map<string, int> m : mapVec)
    {
        fnlMap.insert(m.begin(), m.end());              //adds each countMap in mapVec to this map
    }
    if (fnlMap.empty())                                 //checks if fnlMap is empty
    {
        cerr << "NO PHRASES" << "\n";
        return 0;
    }
    vector<int> freqVector;                             //vector to store frequencies from fnlMap
    map<string, int>::iterator mi;
    for (mi = fnlMap.begin(); mi != fnlMap.end(); mi++)
    {
        freqVector.push_back(mi -> second);             //stores frequencies from fnlMap in freqVector
    }
    if(all_of(freqVector.begin() + 1, freqVector.end(), [&](const int& i){return i == freqVector.front();}))
    {
        cout << "ALL PHRASES EQUALLY FREQUENT" << "\n"; //this was really annoying to figure out how to use, but it basically
        return 0;                                       //checks if every element of freqVector is the same as the first element of freqVector
    }                                                   //if so, then the error message is printed.
    else if ((strcmp(argv[2], "all")) == 0)             //checks if mode is "all" and prints statistics accordingly
    {
        for (mi = fnlMap.begin(); mi != fnlMap.end(); mi++) cout << mi -> first << " " << mi -> second << "\n";
    }
    else if ((strcmp(argv[2], "top")) == 0)             //checks if mode is "top" and prints statistics accordingly
    {
        map<int, string> freqMap;                       //used to store the swapped keys and values of fnlMap
        for (mi = fnlMap.begin(); mi != fnlMap.end(); mi++) freqMap[mi -> second] = mi -> first; //swaps keys and values of fnlMap, adding them to freqMap
        cout << freqMap.rbegin() -> second << " " << freqMap.rbegin() -> first << "\n"; //prints out the phrase with the highest frequency according to freqMap
    }
    return 0;
}
