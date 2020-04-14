#pragma once
#include <memory>
#include <list>
#include <string>
#include "lexer/token.hpp"
#include <iostream>
#include <vector>
#include <cctype>

class parser {

private:
    list<shared_ptr <token> > tokenList;
    struct nonTerminal
    {
        string type; // stores the name of the nonTerminal 
        vector<string> Productions; //this will store the productions of the non-terminal. 
        vector<char> followSet;   //this vector holds all the follow items for nonTerminal
        vector<char> firstSet;    //this vector holds all the first items for nonTerminal
    };

    vector< shared_ptr<nonTerminal> > listNT; //all the nonTerminals will be stored here.
    vector<string> MyProductions; //vector of productions for first().
    string ParseTable[35][20];
    vector<string> doneR;

    void first(shared_ptr<nonTerminal>, char, int, int, int);
    void follow(shared_ptr<nonTerminal> Current);
    void followfirst(shared_ptr<nonTerminal> Current, shared_ptr<nonTerminal> other  , string production ,int pos);
    void addGrammar();
    shared_ptr<nonTerminal> producer;
    void add(shared_ptr<nonTerminal> Current, char c);
    void PopulatPtable(string, string, string);//production, terminal, non-terminal
    void initTable();

public:
    parser();
    parser(list<shared_ptr <token> >);
    ~parser();
    void start();
    
};