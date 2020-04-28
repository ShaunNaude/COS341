#pragma once
#include "lexer/token.hpp"
#include<parser/SyntaxTree.hpp>
#include <memory>
#include <list>
#include <bits/stdc++.h>

class syntaxAnalysis {

    public:
    syntaxAnalysis();
    syntaxAnalysis(list<shared_ptr <token> > , shared_ptr<SyntaxTree>);
    ~syntaxAnalysis();

    private:
    

    //private variables
    list<shared_ptr <token> > tokenList;
    shared_ptr<SyntaxTree> Tree;
    bool error = false;

    //private functions
    void scopeNodes();
    void rename(int);
    void errorCheck(vector< vector< pair<string,string>  > >);





    //debug function
    void debugPrint();
};