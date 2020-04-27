#include "syntaxAnalysis/syntaxAnalysis.hpp"

syntaxAnalysis::syntaxAnalysis(list<shared_ptr <token> > tokenList, shared_ptr<SyntaxTree> Tree) {

    this->tokenList = tokenList;
    this->Tree = Tree;
}

syntaxAnalysis::syntaxAnalysis() {

}

syntaxAnalysis::~syntaxAnalysis() {

}