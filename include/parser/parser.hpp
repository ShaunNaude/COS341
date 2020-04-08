#pragma once
#include <memory>
#include <list>
#include <string>
#include "lexer/token.hpp"
#include <iostream>
#include <vector>

class parser {

private:
    list<shared_ptr <token> > tokenList;
    struct nonTerminal
    {
        string type; // stores the name of the nonTerminal 
        vector<string> Productions; // this will store the productions of the non-terminal. 
    };

    vector< shared_ptr<nonTerminal> > listNT; //all the nonTerminals will be stored here.
    




public:
    parser();
    parser(list<shared_ptr <token> >);
    ~parser();
    void start();
    void addGrammar();
};