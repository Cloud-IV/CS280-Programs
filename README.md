# CS280-Programs
A collection of C++ programs I wrote while learning C++ and about programming language concepts in college.

Assignment 0 is just an introduction to C++ and was meant for me to choose and get used to a development environment. It required me to read in a string and based on the first character of the string, perform different manipulations on the string.

Assignment 1 is my first real programming assignment in C++. Over the course of three parts, I was to achieve the end goal of being able to read words from files and print out statistical information about the frequencies of all the phrases that could be made from the words in those files based on a given mode. This required me to implement vectors, various types of maps, and iterators to achieve my goal. 

Assignment 2, over the course of three parts, required me to build my own lexical analyzer for a primitive language consisting of identifiers, integer constants, string constants, reserved keywords, and operators. Using a given header file, I was to implement two programs:
  1. The Lexical Analyzer: it must be able to recognize the aforementioned tokens via the usage of the given header file ("tokens.h"). Upon      
     recognizing the appropriate token, it would return a Token of that type (for example, upon encountering a '+', it would return a Token
     of type PLUS).
  2. The Test Program: this program calls the GetNextToken() method defined in the lexical analzyer repeatedly until an ERR (error) or DONE
     Token is returned. Depending on various command line arguments passed, it would keep and print various statistics about the number and
     type of Tokens encountered.

Similar to Assignment 2, Assignment 3 required me to build a parser that utilizes the lexical analyzer from Assignment 2 to function. It identifies valid combinations of Tokens as defined in Assignment 2. Using various header files, I was to implement two programs:
  1. The Parser: this is the program that recognizes valid combinations of Tokens and produces a parse tree if the input was succesfully   
     parsed. It utilizes a recursive descent parser that defines a function for each terminal symbol.
  2. The Test Program: this program calls the parser repeatedly in a similar fashion as how the test program in Assignment 2 repeatedly    
     called the lexical anaylzer. Also contains error checking and statistics handling.
*Part 2 is missing because I overwrote Part 1 with Part 3 and forgot to save it as a separate file. The main difference between part 2 and part 3 was dealing with how to handle operators for the lower precendence levels of the parse tree versus the higher precedence levels.
