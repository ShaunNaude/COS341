#pragma once
#include <memory>
#include <list>
#include <string>
#include "lexer/token.hpp"
#include <iostream>
#include <vector>
#include <cctype>
#include <fstream>
#include<parser/SyntaxTree.hpp>
#include <algorithm>

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

    vector<pair<string,int>> stack; // this is going to be the stack we use for parsing, we just going to pretend the vector is a stack
    vector<char> TheFirst;
    vector< shared_ptr<nonTerminal> > listNT; //all the nonTerminals will be stored here.
    vector<string> MyProductions; //vector of productions for first().
    string ParseTable[35][20];


    void first(shared_ptr<nonTerminal>, char, int, int, int);
    void follow(shared_ptr<nonTerminal> Current);
    void followfirst(shared_ptr<nonTerminal> Current, shared_ptr<nonTerminal> other  , string production ,int pos);
    void addGrammar();
    shared_ptr<nonTerminal> producer;
    void add(shared_ptr<nonTerminal> Current, char c);
    void PopulatPtable(string, string, string);//production, terminal, non-terminal
    void initTable();
    string map(string);
    
    void doMapping(); // this will modify the tokenList to have our new mappings

    void Parse();
    void progRule(auto it,int,int,int);
    void procRule(auto it,int,int,int); 
    void DECLRule(auto it,int,int,int);
    void codeRule(auto it,int,int,int);
    

public:
    parser();
    parser(list<shared_ptr <token> >);
    ~parser();
    void start();
    shared_ptr<SyntaxTree> Tree;
    bool syntaxError = false;
    
};