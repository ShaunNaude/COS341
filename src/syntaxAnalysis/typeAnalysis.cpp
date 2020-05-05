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

void typeAnalysis::typeCheck(){
    error = hasValue();
    if(error==false){
        error = ruleValidate();
    }else{
        ruleValidate();
    }
}

void typeAnalysis::errorPrint(){//function to display errors

}

bool typeAnalysis::ruleValidate(){

}

bool typeAnalysis::hasValue(){
    bool ret = false;
    vector< shared_ptr<SyntaxTree::node> > open;
    open.push_back(Tree->root);
    shared_ptr<SyntaxTree::node> temp;
    string procName="";

    while(!open.empty()){
        temp=open.back();
        open.pop_back();

        if(temp->name=="PROC"){//set current procedures name and display error if one is found
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    procName=temp->children[it]->children[0]->name;
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"The procedure "+procName+" is undefined";
                        ret = true;
                    }
                }
            }
        }

        if(temp->name=="VAR"){
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"In the procedure "+procName+" the variable "+temp->children[it]->children[0]->name+" is undefined";
                        ret = true;
                    }
                }
            }
        }

        if(temp->name=="CALL"){
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"In the procedure "+procName+" the call to "+temp->children[it]->children[0]->name+" is undefined";
                        ret = true;
                    }
                }
            }
        }

        for(int it = temp->children.size()-1; it > -1; it--)
            open.push_back(temp->children[it]);
    }

    return ret;
}