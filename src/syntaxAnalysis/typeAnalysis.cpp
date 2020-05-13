#include "syntaxAnalysis/typeAnalysis.hpp"

typeAnalysis::typeAnalysis(list<shared_ptr <token> > tokenList, shared_ptr<SyntaxTree> Tree) {

    this->tokenList = tokenList;
    this->Tree = Tree;
    typeCheck();
    Print();
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

void typeAnalysis::Print(){//function to display errors
    vector< pair< shared_ptr<SyntaxTree::node> , int > > open;
    pair<shared_ptr<SyntaxTree::node> , int > p;
    p.first = Tree->root;
    p.second = 0;
    int num;
    open.push_back(p);
    shared_ptr<SyntaxTree::node> temp;
    ofstream outfile;
    outfile.open("syntaxTree.txt");

    while(open.empty() == false)
    {
        
        p.first = open.back().first;
        auto copy = p.first;
        num = open.back().second;
        
        open.pop_back();
      
        //display indents
        for(int i = 0 ; i<num ; i++ )
            outfile<<"| ";

         if(p.first->tableNode->varibleID != "")
         outfile<<"└─"<<p.first->ID<<": "<<p.first->tableNode->varibleID<<"             "<<p.first->tableNode->type<<endl;

        else outfile<<"└─"<<p.first->ID<<": "<<p.first->name<<"             "<<p.first->tableNode->type<<endl;

        for(auto it = copy->children.begin(); it != copy->children.end(); it++)
        {
            p.first = (*it);
            p.second = num+1;
            open.push_back(p);
        }
            
        

    }
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
                        temp->children[temp->children.size()-1]->tableNode->type="N";
                    }
                }else if(temp->children[temp->children.size()-1]->name=="string"){
                    if(temp->tableNode->type!="S"){
                        changed=true;
                        temp->tableNode->type="S";
                        temp->children[temp->children.size()-1]->tableNode->type="S";
                    }
                }else if(temp->children[temp->children.size()-1]->name=="bool"){
                    if(temp->tableNode->type!="B"){
                        changed=true;
                        temp->tableNode->type="B";
                        temp->children[temp->children.size()-1]->tableNode->type="S";
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
            }
            if(temp->name=="VAR"){
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
                    if(temp->children[temp->children.size()-1]->tableNode->type=="N"){
                        if(temp->tableNode->type!="N"){
                            changed=true;
                            temp->tableNode->type="N";
                        }
                    }
                }else if(temp->children[temp->children.size()-1]->name=="integerLiteral"){//---------------------------------to be checked from
                    if(temp->children[temp->children.size()-1]->tableNode->type!="N"||temp->tableNode->type!="N"){
                        changed=true;
                        temp->children[temp->children.size()-1]->tableNode->type="N";
                        temp->tableNode->type="N";
                    }
                }else if(temp->children[temp->children.size()-1]->name=="CALC"){
                    if(temp->children[temp->children.size()-1]->tableNode->type=="N"){
                        if(temp->tableNode->type!="N"){
                            changed=true;
                            temp->tableNode->type="N";
                        }
                    }
                }
            }
            //CALC
            if(temp->name=="CALC"){
                if(temp->children[temp->children.size()-1]->name=="add"){
                    if(temp->children[temp->children.size()-2]->tableNode->type=="N"&&temp->children[temp->children.size()-3]->tableNode->type=="N"){
                        if(temp->tableNode->type!="N"){
                            changed=true;
                            temp->tableNode->type="N";
                        }
                    }
                }else if(temp->children[temp->children.size()-1]->name=="sub"){
                    if(temp->children[temp->children.size()-2]->tableNode->type=="N"&&temp->children[temp->children.size()-3]->tableNode->type=="N"){
                        if(temp->tableNode->type!="N"){
                            changed=true;
                            temp->tableNode->type="N";
                        }
                    }
                }else if(temp->children[temp->children.size()-1]->name=="mult"){
                    if(temp->children[temp->children.size()-2]->tableNode->type=="N"&&temp->children[temp->children.size()-3]->tableNode->type=="N"){
                        if(temp->tableNode->type!="N"){
                            changed=true;
                            temp->tableNode->type="N";
                        }
                    }
                }
            }
            //BOOL
            if(temp->name=="BOOL"){
                if(temp->children[temp->children.size()-1]->name=="eq"){
                    if(temp->children[temp->children.size()-2]->tableNode->type!=""){
                        if(temp->children[temp->children.size()-2]->tableNode->type==temp->children[temp->children.size()-3]->tableNode->type){
                            if(temp->tableNode->type!="B"){
                                changed=true;
                                temp->tableNode->type="B";
                            }
                        }
                    }
                }else if(temp->children[temp->children.size()-1]->name=="not"){
                    if(temp->children[temp->children.size()-2]->tableNode->type=="B"){
                        if(temp->tableNode->type!="B"){
                            changed=true;
                            temp->tableNode->type="B";
                        }
                    }
                }else if(temp->children[temp->children.size()-1]->name=="and"){
                    if(temp->children[temp->children.size()-2]->tableNode->type=="B"&&temp->children[temp->children.size()-3]->tableNode->type=="B"){
                        if(temp->tableNode->type!="B"){
                            changed=true;
                            temp->tableNode->type="B";
                        }
                    }
                }else if(temp->children[temp->children.size()-1]->name=="or"){
                    if(temp->children[temp->children.size()-2]->tableNode->type=="B"&&temp->children[temp->children.size()-3]->tableNode->type=="B"){
                        if(temp->tableNode->type!="B"){
                            changed=true;
                            temp->tableNode->type="B";
                        }
                    }
                }else if(temp->children[temp->children.size()-1]->name=="T"){
                    temp->children[temp->children.size()-1]->tableNode->type="B";
                    if(temp->tableNode->type!="B"){
                        changed=true;
                        temp->tableNode->type="B";
                    }
                }else if(temp->children[temp->children.size()-1]->name=="F"){
                    temp->children[temp->children.size()-1]->tableNode->type="B";
                    if(temp->tableNode->type!="B"){
                        changed=true;
                        temp->tableNode->type="B";
                    }
                }else if(temp->children.size()==2){//----------------------------------------------------------------------------------------
                    if(temp->children[0]->tableNode->type=="N"&&temp->children[1]->tableNode->type=="N"){
                        if(temp->tableNode->type!="B"){
                            changed=true;
                            temp->tableNode->type="B";
                        }
                    }
                }else if(temp->children.size()==1){
                    if(temp->children[0]->name=="VAR"){
                        if(temp->tableNode->type!="B"){
                            if(temp->children[0]->tableNode->type=="B"){
                                changed=true;
                                temp->tableNode->type="B";
                            }
                        }
                    }
                }//----------------------------------------------------------------------------------------------------------to
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
    int c=0;
    int line = 0, col = 0;

    while(!open.empty()){
        temp=open.back();
        open.pop_back();

        if(temp->name=="PROC"){//set current procedures name and display error if one is found
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    procName=temp->children[it]->children[0]->name;
                }
            }
        }

        //IO/CALLS
        if(temp->name=="IO"){
            if(temp->children[0]->name=="VAR"){
                if(temp->children[0]->tableNode->type!="N"&&temp->children[0]->tableNode->type!="B"&&temp->children[0]->tableNode->type!="S"){
                    cout<<"TYPE ERROR: "<<"In the procedure "<<procName<<" "<<temp->children[0]->children[0]->children[0]->name<<" is not of the correct type(num, string, bool)"<<endl;
                }
            }
        }else
        if(temp->name=="CALL"){
            if(temp->children[0]->name=="userDefined"){
                if(temp->children[0]->tableNode->type!="P"){
                    cout<<"TYPE ERROR: "<<"In the procedure "<<procName<<" the procedure "<<temp->children[0]->children[0]->name<<" was not declared in this scope"<<endl;
                }
            }
        }else
        //ASSIGN
        if(temp->name=="ASSIGN"){
            if(temp->children[0]->name=="stringLiteral"){
                if(temp->children[temp->children.size()-1]->tableNode->type!="S"){
                    cout<<"TYPE ERROR: "<<"In procedure "<<procName<<temp->children[temp->children.size()-1]->children[0]->children[0]->name<<" is not a string"<<endl;
                }
            }else if(temp->children[0]->name=="VAR"){
                if(temp->children[temp->children.size()-1]->tableNode->type!=temp->children[0]->tableNode->type){
                    cout<<"TYPE ERROR: "<<"In procedure "<<procName<<temp->children[temp->children.size()-1]->children[0]->children[0]->name<<" is not of the same type as "<<temp->children[0]->children[0]->children[0]->name<<endl;
                }
            }else if(temp->children[0]->name=="NUMEXPR"){
                if(temp->children[temp->children.size()-1]->tableNode->type!="N"){
                    cout<<"TYPE ERROR: "<<"In procedure "<<procName<<" "<<temp->children[temp->children.size()-1]->children[0]->children[0]->name<<" is not a number"<<endl;
                }
            }else if(temp->children[0]->name=="BOOL"){
                if(temp->children[temp->children.size()-1]->tableNode->type!="B"){
                    cout<<"TYPE ERROR: "<<"In procedure "<<procName<<temp->children[temp->children.size()-1]->children[0]->children[0]->name<<" is not a bool"<<endl;
                }
            }
        }else
        //COND BRANCH
        if(temp->name=="COND_BRANCH"){
            if(temp->children[temp->children.size()-1]->name=="if"){
                if(temp->children[temp->children.size()-2]->tableNode->type!="B"){
                    cout<<"TYPE ERROR: "<<"In procedure "<<procName<<" there is a problem with the boolean expression in an if statement"<<endl;
                }
            }
        }else
        //COND LOOP
        if(temp->name=="COND_LOOP"){
            if(temp->children[temp->children.size()-1]->name=="while"){
                if(temp->children[temp->children.size()-2]->tableNode->type!="B"){
                    cout<<"TYPE ERROR: "<<"In procedure "<<procName<<" there is a problem with the boolean expression in a while loop"<<endl;
                }
            }else if(temp->children[temp->children.size()-1]->name=="for"){
                for(int it = 0; it < temp->children.size(); it++){
                    c++;
                    if(temp->children[it]->name=="VAR"){
                        if(temp->children[it]->tableNode->type!="N"){
                            cout<<"TYPE ERROR: "<<"In procedure "<<procName<<" there is a problem with VAR number "<<c<<" not being a number"<<endl;
                        }
                    }
                }
                c=0;
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
    int line = 0, col = 0;

    while(!open.empty()){
        temp=open.back();
        open.pop_back();

        if(temp->name=="VAR"){
            if(temp->children[0]->name=="userDefined"){
                if(temp->children[0]->children[0]->tableNode->varibleID!="U"){
                    temp->children[0]->tableNode->type=temp->children[0]->children[0]->tableNode->type;
                    temp->tableNode->type=temp->children[0]->tableNode->type;
                }
            }
        }
        if(temp->name=="CALL"){
            if(temp->children[0]->name=="userDefined"){
                if(temp->children[0]->children[0]->tableNode->varibleID!="U"){
                    temp->children[0]->tableNode->type=temp->children[0]->children[0]->tableNode->type;
                    temp->tableNode->type=temp->children[0]->tableNode->type;
                }
            }
        }

        if(temp->name=="PROC"){//set current procedures name and display error if one is found
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    procName=temp->children[it]->children[0]->name;
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"TYPE ERROR: "<<"The procedure "+procName+" is undefined"<<endl;
                        ret = true;
                    }
                }
            }
        }

        if(temp->name=="VAR"){
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"TYPE ERROR: "<<"In the procedure "+procName+" the variable "+temp->children[it]->children[0]->name+" is undefined"<<endl;
                        ret = true;
                    }
                }
            }
        }

        if(temp->name=="NAME"){
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"TYPE ERROR: "<<"In the procedure "+procName+" the variable "+temp->children[it]->children[0]->name+" is undefined"<<endl;
                        ret = true;
                    }
                }
            }
        }

        if(temp->name=="CALL"){
            for(int it = temp->children.size()-1; it > -1; it--){
                if(temp->children[it]->name=="userDefined"){
                    if(temp->children[it]->children[0]->tableNode->varibleID=="U"){
                        cout<<"TYPE ERROR: "<<"In the procedure "+procName+" the call to "+temp->children[it]->children[0]->name+" is undefined"<<endl;
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