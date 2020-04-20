#include "parser/SyntaxTree.hpp"

SyntaxTree::SyntaxTree() {

}

SyntaxTree::~SyntaxTree() {

}

int SyntaxTree::createTree(string rootName)
{

    this->root = make_shared<node>();
    root->ID = num++;
    root->name = rootName;
    

}

int SyntaxTree::addNode(int parent , string child)
{

}