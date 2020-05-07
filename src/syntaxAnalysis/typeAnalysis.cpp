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

void typeAnalysis::typeSet(){
    vector< shared_ptr<SyntaxTree::node> > open;
    open.push_back(Tree->root);
    shared_ptr<SyntaxTree::node> temp;
    bool changed = false;
    do{
        changed = false;
        open.push_back(Tree->root);
        while(!open.empty()){
            temp=open.back();
            open.pop_back();

            //CODE
            if(temp->name=="PROC"){
                for(int it = temp->children.size()-1; it > -1; it--){
                    if(temp->children[it]->name=="userDefined"){
                        if(temp->children[it]->tableNode->type!="P"){
                            changed=true;
                            temp->children[it]->tableNode->type="P";
                        }
                    }
                }
            }
            //TYPE
            if(temp->name=="TYPE"){
                if(temp->children[temp->children.size()-1]->name=="num"){
                    if(temp->tableNode->type!="N"){
                        changed=true;
                        temp->tableNode->type="N";
                    }
                }else if(temp->children[temp->children.size()-1]->name=="string"){
                    if(temp->tableNode->type!="S"){
                        changed=true;
                        temp->tableNode->type="S";
                    }
                }else if(temp->children[temp->children.size()-1]->name=="bool"){
                    if(temp->tableNode->type!="B"){
                        changed=true;
                        temp->tableNode->type="B";
                    }
                }
            }
            if(temp->name=="DECL"){
                if(temp->children[temp->children.size()-1]->name=="TYPE"){
                    if(temp->children[temp->children.size()-2]->tableNode->type!=temp->children[temp->children.size()-1]->tableNode->type){
                        changed=true;
                        temp->children[temp->children.size()-2]->tableNode->type=temp->children[temp->children.size()-1]->tableNode->type;
                    }
                }
            }
            //ASSIGN
            if(temp->name=="NAME"){
                if(temp->children[temp->children.size()-1]->name=="userDefined"){
                    if(temp->tableNode->type!=temp->children[temp->children.size()-1]->tableNode->type){
                        changed=true;
                        temp->children[temp->children.size()-1]->tableNode->type=temp->tableNode->type;
                    }
                }
            }else if(temp->name=="VAR"){
                if(temp->children[temp->children.size()-1]->name=="userDefined"){
                    if(temp->tableNode->type!=temp->children[temp->children.size()-1]->tableNode->type){
                        changed=true;
                        temp->children[temp->children.size()-1]->tableNode->type=temp->tableNode->type;
                    }
                }
            }
            //NUMEXPR
            if(temp->name=="NUMEXPR"){
                if(temp->children[temp->children.size()-1]->name=="VAR"){
                
                }else if(temp->children[temp->children.size()-1]->name=="integerLiteral"){
                
                }else if(temp->children[temp->children.size()-1]->name=="CALC"){
                
                }
            }
            //CALC
            if(temp->name=="CALC"){
                if(temp->children[temp->children.size()-1]->name=="add"){
                
                }else if(temp->children[temp->children.size()-1]->name=="sub"){
                
                }else if(temp->children[temp->children.size()-1]->name=="mult"){
                
                }
            }
            //BOOL
            if(temp->name=="BOOL"){
                if(temp->children[temp->children.size()-1]->name=="eq"){
                
                }else if(temp->children[temp->children.size()-1]->name=="not"){

                }else if(temp->children[temp->children.size()-1]->name=="and"){

                }else if(temp->children[temp->children.size()-1]->name=="or"){

                }else if(temp->children[temp->children.size()-1]->name=="T"){

                }else if(temp->children[temp->children.size()-1]->name=="F"){

                }else if(temp->children.size()==3){
                    if(temp->children[1]->name=="<"){

                    }else if(temp->children[1]->name==">"){

                    }
                }else if(temp->children.size()==1){
                    if(temp->children[0]->name=="VAR"){
                
                    }
                }
            }

            for(int it = temp->children.size()-1; it > -1; it--)
                open.push_back(temp->children[it]);
        }
    }while(changed==true);
}

bool typeAnalysis::ruleValidate(){
    typeSet();
    bool ret = false;
    vector< shared_ptr<SyntaxTree::node> > open;
    open.push_back(Tree->root);
    shared_ptr<SyntaxTree::node> temp;
    string procName="";

    while(!open.empty()){
        temp=open.back();
        open.pop_back();

        //IO/CALLS
        if(temp->name=="IO"){
            
        }else
        if(temp->name=="CALL"){
            
        }else
        //ASSIGN
        if(temp->name=="ASSIGN"){
            if(temp->children[0]->name=="stringLiteral"){

            }else if(temp->children[0]->name=="VAR"){

            }else if(temp->children[0]->name=="NUMEXPR"){

            }else if(temp->children[0]->name=="BOOL"){

            }
        }else
        //COND BRANCH
        if(temp->name=="COND_BRANCH"){
            if(temp->children[temp->children.size()-1]->name=="if"){
                
            }
        }else
        //COND LOOP
        if(temp->name=="COND_LOOP"){
            if(temp->children[temp->children.size()-1]->name=="while"){

            }else if(temp->children[temp->children.size()-1]->name=="for"){

            }
        }

        for(int it = temp->children.size()-1; it > -1; it--)
            open.push_back(temp->children[it]);
    }

    return ret;
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
                        cout<<"The procedure "+procName+" is undefined"<<endl;
                        ret = true;
                    }
                }
            }
        }

        if(temp->name=="VAR"){
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"In the procedure "+procName+" the variable "+temp->children[it]->children[0]->name+" is undefined"<<endl;
                        ret = true;
                    }
                }
            }
        }

        if(temp->name=="NAME"){
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"In the procedure "+procName+" the variable "+temp->children[it]->children[0]->name+" is undefined"<<endl;
                        ret = true;
                    }
                }
            }
        }

        if(temp->name=="CALL"){
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"In the procedure "+procName+" the call to "+temp->children[it]->children[0]->name+" is undefined"<<endl;
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