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

    return root->ID;
    

}

int SyntaxTree::addNode(int parent , string child)
{

    //find parent
    vector< shared_ptr<node> > open;
    bool found = false;
    open.push_back(root);
    shared_ptr<node> temp;

    while(open.empty() == false && found==false)
    {
        
        temp = open.back();
        open.pop_back();

        if(temp->ID == parent)
        {
            found = true;
        }
        else{
            for(auto it = temp->children.begin(); it != temp->children.end(); it++)
                open.push_back((*it));
        }

    }

    if(found == true)
    {
        shared_ptr<node> newChild = make_shared<node>();
        newChild->ID = num++;
        newChild->name = child;
        temp->children.push_back(newChild);
        return newChild->ID;

    }
    else{
        cout<<"fuck bois we have an error"<<endl;
        return -1;
    }



}