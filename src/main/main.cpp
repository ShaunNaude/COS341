#include <iostream>
#include <lexer/lexer.hpp>

using namespace std;

int main() {
    /*
    *======================================================================================
    *                           Action Plan 
    *======================================================================================
    
    *   1) The main function will give the lexer class the name of the textfile that needs to
    *      be tokenized.
    * 
    *   2) All the logic for creating tokens will be within the lexer class.
    * 
    *   3) The lexer class will have the doubly linked list of type token,it will be 
    *      the lexer classes responsiblity to write the linked list of tokens to the txt file.
    * 
    *   4) The lexer class is also supposed to write all errors to a textfile.
    * 
    * 
    * ====================================================================================== 
    *                           Application
    * ====================================================================================== 
    *   main  
    *   1) Pass textfile to lexer from main.
    *   2) Read in textfile and make it a string
    *   Lexer
    *   Function LexString(string):
    *   3) Lexer will create token linked list of tokens.(function).
    *   4) Loop till end of string(char by char).
    *   5) Loop till end of line(#). At end reset error checking.
    *   6) Run functions:
    *       isOperator(string, int);
    *       isKeyword(string, int); return int of position in string to continue from.
    *       isString(string, int);
    *       isVar(string, int);
    *       isInt(string, int);
    *   7) Additional Functions;
    *       AddNode(string, int, int); add token to linked list from to string positions.
    *       
    * */

    
    








}