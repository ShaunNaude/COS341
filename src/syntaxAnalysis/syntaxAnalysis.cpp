#include "syntaxAnalysis/syntaxAnalysis.hpp"

syntaxAnalysis::syntaxAnalysis(list<shared_ptr <token> > tokenList, shared_ptr<SyntaxTree> Tree) {

    this->tokenList = tokenList;
    this->Tree = Tree;
    scopeNodes();
}

syntaxAnalysis::syntaxAnalysis() {

}

syntaxAnalysis::~syntaxAnalysis() {

}

void syntaxAnalysis::scopeNodes(){
    //here i need to traverse the tree and scope the varibles
    vector< shared_ptr<SyntaxTree::node> > open;
    open.push_back(Tree->root);
    shared_ptr<SyntaxTree::node> temp;
    int scope = 0;

    while(open.empty() == false)
    {
        temp = open.back();
       open.pop_back();
      

       
        temp->tableNode->scope = scope;

        if(temp->name == "proc")
            ++scope;
        

        for(int it = temp->children.size()-1; it > -1; it--)
                open.push_back(temp->children[it]);


    }

    rename(scope);

    debugPrint();

    

    
}

 void syntaxAnalysis::rename(int scopeNum){
                        //NAME,TYPE
     vector< vector< pair<string,string>  > > declarations;
     vector< pair<string,string> > tempList;
     pair<string,string> p ;
     bool stop=false;
     int num = 0;

     for(int i = 0  ; i<scopeNum+1 ; i++)
     {

         vector< shared_ptr<SyntaxTree::node> > open;
        open.push_back(Tree->root);
        shared_ptr<SyntaxTree::node> temp;
        stop = false;

        while(open.empty() == false && stop == false)
        {
            temp = open.back();
            open.pop_back();

            if(temp->tableNode->scope == i )
                {   
                    if(temp->name == "DECL")
                    {
                    if(temp->children[0]->name == "DECL")
                        num++;
                    //name
                    p.first = temp->children[num]->children[0]->children[0]->name;
                    

                    //type
                    p.second = temp->children[num+1]->children[0]->name;

                    //set the actual varible type
                    temp->children[num]->children[0]->children[0]->tableNode->type = p.second;

                    //add pair to vector
                    tempList.push_back(p);

                    num=0;
                    }

                }

               // if(temp->tableNode->scope > i)
               // {
                   //if(tempList.size() != 0)
                    //declarations.push_back(tempList);

                    //tempList.clear();
                    //stop = true;
                    //open.clear();
                   // continue;
               // }

            

            for(auto it = temp->children.begin(); it != temp->children.end(); it++)
                open.push_back((*it));

        }//end while loop

        declarations.push_back(tempList);
        tempList.clear();


     }//end for loop

     //once we here we have our declarations, check for duplicate declarations
       errorCheck(declarations); 

        if(error != false)
        {
            cout<<"Error: please make varibles within same scope unique"<<endl;
            return;
        }

        //


 }



void syntaxAnalysis::errorCheck( vector< vector< pair<string,string>  > > declarations ){
    // we need to now check if we have more than one varible with the same name in the same scope
        // if we do we should log an error.

        for(int i = 0 ; i < declarations.size() ; i++)
        {

            unordered_set <string> stringSet ;

            for(int k = 0 ; k<declarations[i].size() ; k++)
            {

                if (stringSet.find(declarations[i][k].first) == stringSet.end()) 
                    stringSet.insert(declarations[i][k].first); 
                    else{
                        cout<<"ERROR -> varible :'"<<declarations[i][k].first<<"' is defined twice in the same scope"<<endl;
                        error = true;
                    } 


            } //end inner for 

            stringSet.clear();



        }// end outer for



}

void syntaxAnalysis::debugPrint(){
     vector< pair< shared_ptr<SyntaxTree::node> , int > > open;
    pair<shared_ptr<SyntaxTree::node> , int > p;
    p.first = Tree->root;
    p.second = 0;
    int num;
    open.push_back(p);
    shared_ptr<SyntaxTree::node> temp;

    while(open.empty() == false)
    {
        
        p.first = open.back().first;
        auto copy = p.first;
        num = open.back().second;

        open.pop_back();
      
        //display indents
        for(int i = 0 ; i<num ; i++ )
            cout<<"| ";

     
         cout<<"└─"<<p.first->ID<<": "<<p.first->name<<" -> "<<p.first->tableNode->scope<<endl;

        for(auto it = copy->children.begin(); it != copy->children.end(); it++)
        {
            p.first = (*it);
            p.second = num+1;
            open.push_back(p);
        }
            
        

    }
}