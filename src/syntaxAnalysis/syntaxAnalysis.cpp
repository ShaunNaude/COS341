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
      

       
       // temp->tableNode->scope = scope;

        if(temp->name == "proc")
            ++scope;
        temp->tableNode->scope = scope;

        for(int it = temp->children.size()-1; it > -1; it--)
                open.push_back(temp->children[it]);


    }

    rename(scope);

    debugPrint();

    

    
}

 void syntaxAnalysis::rename(int scopeNum) {
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

<<<<<<< HEAD
               // if(temp->tableNode->scope > i)
               // {
                   //if(tempList.size() != 0)
                    //declarations.push_back(tempList);

                    //tempList.clear();
                    //stop = true;
                    //open.clear();
                   // continue;
               // }

            
=======
               
>>>>>>> ShaunDev

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
        renameProcedures(scopeNum);

        //TODO rename varibles here.
//=================================================================
        //loop through tree, 
        //if userdefined and variableID =""
        //then check scope 
        //if scope is fine rename variableID
                    //name //varID
        vector< vector<pair<string,string>> > list;
        list.resize(scopeNum+1);
        vector< shared_ptr<SyntaxTree::node> > open;
        open.push_back(Tree->root);
        shared_ptr<SyntaxTree::node> temp;
        bool gotcha = false;
        int counter=0;
        int currProc_DEF = 0;
        
        num=0;
            //name varID
        pair<string,string> PAIR;
        //renaming variables
        while(open.empty() == false)
        {
            temp = open.back();
            open.pop_back();

            

            if(temp->name == "DECL")
                    {
                    if(temp->children[0]->name == "DECL")
                        num++;
                    //name
                    PAIR.first = temp->children[num]->children[0]->children[0]->name;
                    PAIR.second = "V"+to_string(counter);
                    counter++;
                    //add pair to vector
                    list[temp->children[num]->children[0]->children[0]->tableNode->scope].push_back(PAIR);

                    num=0;
                    }

           
            for(auto it = temp->children.begin(); it != temp->children.end(); it++)
                open.push_back((*it));

            }

        open.push_back(Tree->root);
        counter=0;

        while(open.empty() == false)
        {
            temp = open.back();
            open.pop_back();

            if(temp->name == "PROC_DEFS")
            {
                currProc_DEF = temp->tableNode->scope;
            }

            if(temp->name == "userDefined" && temp->children[0]->tableNode->varibleID == "")
            {
                int currScope =  temp->children[0]->tableNode->scope;
                //get declared scope
                int declared;
                for(int i = 0 ; i<declarations.size() ; i++)
                {
                    for(int j = 0 ; j<declarations[i].size() ; j++)
                    {
                        if(declarations[i][j].first == temp->children[0]->name)
                        {
                            declared = i;
                        }
                    }
                }

                if(currScope<=declared)
                {
                    //find var in list
                    bool found = false;
                    for(int i = 0; i<list[currScope].size() ; i++)
                    {
                        if(list[currScope][i].first == temp->children[0]->name)
                        {
                            temp->children[0]->tableNode->varibleID = list[currScope][i].second;
                            found = true;
                            break;
                        }
                    }
                    //first try find it in list[currscope]
                    //if not there look from end of list till start
                    if(found == false)
                    {
                        bool good = false;
                        if(currProc_DEF == 0)
                        {
                            for(int i = 0 ; i<list[list.size()-1].size() ; i++)
                            {
                                if(temp->children[0]->name == list[list.size()-1][i].first)
                                {
                                    good = true;
                                    temp->children[0]->tableNode->varibleID = list[list.size()-1][i].second;
                                    break;
                                }
                            }
                            if(good == false)
                            {
                                temp->children[0]->tableNode->varibleID = "U";
                            }
                        }

                        else{
                        bool shap = false;
                        for(int i = list.size()-1 ; i>-1 ; i--)
                        {
                            if(shap == true)
                                break;
                            for(int j = 0 ; j<list[i].size() ; j++)
                            {
                                if(list[i][j].first == temp->children[0]->name)
                                {
                                    temp->children[0]->tableNode->varibleID = list[i][j].second;
                                    shap = true;
                                    break;
                                }
                            }
                        }
                    }


                    }
                    

                }
                else{
                    temp->children[0]->tableNode->varibleID = "U";
                }
                
                        
                    }

           
            for(auto it = temp->children.begin(); it != temp->children.end(); it++)
                open.push_back((*it));

            }
            

            
        
//=================================================================
        
 }

void syntaxAnalysis::renameProcedures(int scopeNum){

    vector< vector<string> > pScopes;
    pScopes.resize(scopeNum+1);

    for(int i = 0 ; i<2 ;i++ )
    {
        if( i == 0 )
        {
            //do top code.
            topLevel(pScopes);
        }

        if(i == 1 )
        {
            //do everything else
            otherProcedures(pScopes);

        }


    }
   
    //make a function to check if we have duplicate proceudures in same scope.
    errorCheckP(pScopes);

     if(error != false)
        {
            cout<<"Error: please make procedures within same scope unique"<<endl;
            return;
        }



        //renaming procedures here
    //=============================================================
        vector< shared_ptr<SyntaxTree::node> > open;
        bool gotcha = false;
        open.push_back(Tree->root);
        shared_ptr<SyntaxTree::node> temp;
                    //name //varID
        vector< pair<string,string> > list;
        int counter=0;
        //renaming procedures
        while(open.empty() == false)
        {
            temp = open.back();
            open.pop_back();

             if(temp->name == "PROC_DEFS")
             {
                if(temp->children.size() == 1)
                {
                temp->children[0]->children[1]->children[0]->tableNode->varibleID = "P"+to_string(counter);
                pair<string,string> p ;
                p.first = temp->children[0]->children[1]->children[0]->name;
                p.second = temp->children[0]->children[1]->children[0]->tableNode->varibleID;
                list.push_back(p);
                }
           else {
               temp->children[1]->children[1]->children[0]->tableNode->varibleID = "P"+to_string(counter);
               pair<string,string> p ;
                p.first = temp->children[1]->children[1]->children[0]->name;
                p.second = temp->children[1]->children[1]->children[0]->tableNode->varibleID;
                list.push_back(p);

           }

                counter++;
             }


             for(auto it = temp->children.begin(); it != temp->children.end(); it++)
                open.push_back((*it));
        
        }

    open.push_back(Tree->root);
        //renaming procedure CALLS
        while(open.empty() == false)
        {
            temp = open.back();
            open.pop_back();

             if(temp->name == "CALL")
             {
                 string name = temp->children[0]->children[0]->name;
                 //check scope
                 //pScopes[temp->children[0]->children[0]->tableNode->scope]

                 for(int i = 0; i < pScopes[temp->children[0]->children[0]->tableNode->scope].size() ; i++ )
                 {
                     if(name == pScopes[temp->children[0]->children[0]->tableNode->scope][i])
                     {
                        
                        for(int k = 0 ; k<list.size() ; k++)
                        {

                            if(name == list[k].first)
                            {
                                temp->children[0]->children[0]->tableNode->varibleID = list[k].second;

                            }

                        }
                            gotcha = true;

                     }
                 }


                if(gotcha == false)
                {
                    temp->children[0]->children[0]->tableNode->varibleID = "U";
                }
                gotcha = false;
             }

             for(auto it = temp->children.begin(); it != temp->children.end(); it++)
                open.push_back((*it));
        
        }

//==============================================================



    

}

void syntaxAnalysis::errorCheckP(vector< vector<string> > pScopes)
{
    for(int i = 0 ; i < pScopes.size() ; i++)
        {

            unordered_set <string> stringSet ;

            for(int k = 0 ; k<pScopes[i].size() ; k++)
            {

                if (stringSet.find(pScopes[i][k]) == stringSet.end()) 
                    stringSet.insert(pScopes[i][k]); 
                    else{
                        cout<<"ERROR -> varible :'"<<pScopes[i][k]<<"' is defined twice in the same scope"<<endl;
                        error = true;
                    } 


            } //end inner for 

            stringSet.clear();

}
}

void syntaxAnalysis::otherProcedures(vector< vector<string> > &pScopes){


        //TODO finish function
        vector< shared_ptr<SyntaxTree::node> > open;
        open.push_back(Tree->root);
        shared_ptr<SyntaxTree::node> temp;
        bool foundOuter = false;
        bool foundInner = false; 
        int Oscope;
        int Iscope;

        while(open.empty() == false)
        {
            temp = open.back();
            open.pop_back();

            if(foundOuter == false)
            {
                if(temp->name == "PROC_DEFS" && temp->tableNode->scope == 0)
                {
                    foundOuter = true;
                    if(temp->children.size() == 1)
                     Oscope = temp->children[0]->children[1]->children[0]->tableNode->scope;
                else Oscope = temp->children[1]->children[1]->children[0]->tableNode->scope;
                }
            }
            else{
                    if(foundInner == false)
                    {
                        if(temp->name == "PROC_DEFS" && temp->tableNode->scope > 0)
                        {
                            Iscope = temp->tableNode->scope;
                            foundInner = true;
                            //add to pscopes at Oscope as placement
                            if(temp->children.size() == 1)
                            pScopes[Oscope].push_back(temp->children[0]->children[1]->children[0]->name);
                            else pScopes[Oscope].push_back(temp->children[1]->children[1]->children[0]->name);

                        }

                    }
                    else{
                            if(temp->name == "PROC_DEFS" && temp->tableNode->scope > Iscope)
                            {
                                //USE THE SCOPE OF proc as placement, get the name
                                int placement = temp->children[0]->children[2]->tableNode->scope;
                                //-> add to pscopes at proc_scope , get the name
                                if(temp->children.size() == 1)
                            pScopes[placement].push_back(temp->children[0]->children[1]->children[0]->name);
                            else pScopes[placement].push_back(temp->children[1]->children[1]->children[0]->name);

                            }

                            if(temp->name == "PROC_DEFS" && temp->tableNode->scope == Iscope)
                            {
                                 //add to pscopes at Oscope as placement
                                  if(temp->children.size() == 1)
                            pScopes[Oscope].push_back(temp->children[0]->children[1]->children[0]->name);
                            else pScopes[Oscope].push_back(temp->children[1]->children[1]->children[0]->name);
                            }

                    }
                    
                    if(temp->name == "PROC_DEFS" && temp->tableNode->scope == 0)
                    {
                        if(temp->children.size() == 1)
                     Oscope = temp->children[0]->children[1]->children[0]->tableNode->scope;
                else Oscope = temp->children[1]->children[1]->children[0]->tableNode->scope;

                foundInner= false;
                       
                    }
                    

            }



            for(auto it = temp->children.begin(); it != temp->children.end(); it++)
                open.push_back((*it));

        }

        return;


}
void syntaxAnalysis::topLevel(  vector< vector<string> > &pScopes)
{
    vector< shared_ptr<SyntaxTree::node> > open;
        open.push_back(Tree->root);
        shared_ptr<SyntaxTree::node> temp;
        

        while(open.empty() == false)
        {
            temp = open.back();
            open.pop_back();

            if(temp->name == "PROC_DEFS" && temp->tableNode->scope == 0)
            {
                if(temp->children.size() == 1)
                pScopes[pScopes.size()-1].push_back(temp->children[0]->children[1]->children[0]->name);
                else pScopes[pScopes.size()-1].push_back(temp->children[1]->children[1]->children[0]->name);
            }


            for(auto it = temp->children.begin(); it != temp->children.end(); it++)
                open.push_back((*it));
        }

        return;

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

     
         cout<<"└─"<<p.first->ID<<": "<<p.first->name<<"|"<<p.first->tableNode->varibleID<<" -> "<<p.first->tableNode->scope<<endl;

        for(auto it = copy->children.begin(); it != copy->children.end(); it++)
        {
            p.first = (*it);
            p.second = num+1;
            open.push_back(p);

        }
            
        

    }
}