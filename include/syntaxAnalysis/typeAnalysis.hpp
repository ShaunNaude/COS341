#pragma once
#include "syntaxAnalysis/syntaxAnalysis.hpp"

class typeAnalysis {

    public:
    typeAnalysis();
    typeAnalysis(list<shared_ptr <token> > , shared_ptr<SyntaxTree>);
    ~typeAnalysis();
    bool error = false;

    private:
    list<shared_ptr <token> > tokenList;
    shared_ptr<SyntaxTree> Tree;

    void typeCheck();
    bool ruleValidate();
    bool hasValue();

    //debug function
    void errorPrint();
};