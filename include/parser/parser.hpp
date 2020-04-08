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
        vector<string> followSet;   //this vector holds all the follow items for nonTerminal
        vector<string> firstSet;    //this vector holds all the first items for nonTerminal
    };

    vector< shared_ptr<nonTerminal> > listNT; //all the nonTerminals will be stored here.
    




public:
    parser();
    parser(list<shared_ptr <token> >);
    ~parser();
    void first();
    void follow();
    void start();
    void addGrammar();
};