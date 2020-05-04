#pragma once
#include "syntaxAnalysis/syntaxAnalysis.hpp"

class typeAnalysis {

    public:
    typeAnalysis();
    typeAnalysis(list<shared_ptr <token> > , shared_ptr<SyntaxTree>);
    ~typeAnalysis();

    private:
    list<shared_ptr <token> > tokenList;
    shared_ptr<SyntaxTree> Tree;
    bool error = false;

    void typeCheck();

    //debug function
    void errorPrint();
};