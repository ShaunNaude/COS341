#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
using namespace std;

class SyntaxTree {


private:

//this int keeps track of the ID number, It will increment each time we add a node.

int num = 0;

public:
    SyntaxTree();
    ~SyntaxTree();
    int createTree(string); // this initailises root
    int addNode(int parent , string child , bool map); // note when we add nodes we need to find the parent first then add the child to the childrens list

    string mapBack(string old);
  

    void makeSymbolTable();
  
    void writeToFile();

    //prune tree
    void prune();

    //remove
    void remove(int ID ,int index);

    //symbol table node that extends the tree node.
struct symbolTableNode{

    //here we will add 
        //scope
        //type etc...
        int scope;
        string varibleID;
        string type;

};

//this is the tree node
struct node{

    string name;

    int ID;

    vector< shared_ptr<node> > children; // each node will have a vector of pointers going to their children.

    shared_ptr<symbolTableNode> tableNode;

};

    shared_ptr<node> root;
    vector< shared_ptr<symbolTableNode> > symbolTable;


};