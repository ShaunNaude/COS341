#pragma once
#include <memory>
#include <list>
#include "lexer/token.hpp"
#include <fstream>
#include <string>

using namespace std;

class lexer {

public:
//=========================Variables============================
    list<shared_ptr <token> > tokenList;
//==============================================================

//=========================Functions============================
    lexer();
    ~lexer();
    void start(string);
private:
    int isOperator(string, int);
    int isKeyword(string, int);
    int isString(string, int);
    int isVar(string, int);
    int isInt(string, int);
    void logError(string);
    void AddNode(string, int, int);
    
    void AddNode(string, int, int, string);

    //Helper functions
    bool OperatorNext(char);
    bool isValid(char);

    //Global varibales
    int currentLine = 1;
};