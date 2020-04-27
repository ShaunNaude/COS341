#pragma once
#include "lexer/token.hpp"
#include<parser/SyntaxTree.hpp>
#include <memory>
#include <list>

class syntaxAnalysis {

    public:
    syntaxAnalysis();
    syntaxAnalysis(list<shared_ptr <token> > , shared_ptr<SyntaxTree>);
    ~syntaxAnalysis();

    private:
    

    //private variables
    list<shared_ptr <token> > tokenList;
    shared_ptr<SyntaxTree> Tree;

    //private functions
};