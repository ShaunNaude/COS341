#include "syntaxAnalysis/typeAnalysis.hpp"

typeAnalysis::typeAnalysis(list<shared_ptr <token> > tokenList, shared_ptr<SyntaxTree> Tree) {

    this->tokenList = tokenList;
    this->Tree = Tree;
    typeCheck();
}

typeAnalysis::typeAnalysis() {

}

typeAnalysis::~typeAnalysis() {

}

void typeCheck::typeCheck(){
    vector< shared_ptr<SyntaxTree::node> > open;
    open.push_back(Tree->root);
    shared_ptr<SyntaxTree::node> temp;

    
}

void typeCheck::errorPrint(){

}