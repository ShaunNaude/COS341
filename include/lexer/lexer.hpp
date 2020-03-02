#pragma once

class lexer {

public:
    lexer();
    ~lexer();
    void start(string);
private:
    int isOperator(string, int);
    int isKeyword(string, int);
    int isString(string, int);
    int isVar(string, int);
    int isInt(string, int);
    
    void AddNode(string, int, int);
};