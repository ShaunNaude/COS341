#include "parser/SyntaxTree.hpp"

SyntaxTree::SyntaxTree() {

}

SyntaxTree::~SyntaxTree() {

}

int SyntaxTree::createTree(string rootName)
{

    this->root = make_shared<node>();
    root->ID = num++;
    root->name = mapBack(rootName);

    return root->ID;
    

}

int SyntaxTree::addNode(int parent , string child, bool map)
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
        if(map == true)
        {
            child = mapBack(child);
        }


        newChild->name = child;
        temp->children.push_back(newChild);
        return newChild->ID;

    }
    else{
        cout<<"fuck bois we have an error"<<endl;
        return -1;
    }



}

string SyntaxTree::mapBack(string old){
    if(old == "A")
    {
        return "PROG";
    }
     if(old == "B")
    {
        return "PROC_DEFS";
    }
     if(old == "C")
    {
        return "PROC";
    }
     if(old == "D")
    {
        return "CODE";
    }
     if(old == "E")
    {
        return "INSR";
    }
     if(old == "F")
    {
        return "DECL";
    }
     if(old == "G")
    {
        return "IO";
    }
     if(old == "H")
    {
        return "CALL";
    }
     if(old == "I")
    {
        return "ASSIGN";
    }
     if(old == "J")
    {
        return "COND_BRANCH";
    }
     if(old == "K")
    {
        return "COND_LOOP";
    }
     if(old == "L")
    {
        return "TYPE";
    }
     if(old == "M")
    {
        return "NAME";
    }
     if(old == "N")
    {
        return "VAR";
    }
     if(old == "O")
    {
        return "NUMEXPR";
    }
    if(old == "P")
    {
        return "CALC";
    }
    if(old == "Q")
    {
        return "BOOL";
    }

     if(old == "a")
    {
        return "proc";
    }
     if(old == "b")
    {
        return "userDefined";
    }
    if(old == "c")
    {
        return "halt";
    }
     if(old == "d")
    {
        return "input";
    }
    if(old == "e")
    {
        return "output";
    }
     if(old == "f")
    {
        return "stringLiteral";
    }
    if(old == "g")
    {
        return "integerLiteral";
    }
     if(old == "h")
    {
        return "add";
    }
    if(old == "i")
    {
        return "sub";
    }
     if(old == "j")
    {
        return "mult";
    }
     if(old == "k")
    {
        return "if";
    }
     if(old == "l")
    {
        return "then";
    }
     if(old == "m")
    {
        return "else";
    }
     if(old == "n")
    {
        return "eq";
    }
     if(old == "o")
    {
        return "not";
    }
     if(old == "p")
    {
        return "and";
    }
    if(old == "q")
    {
        return "or";
    }
    if(old == "r")
    {
        return "T";
    }
    if(old == "s")
    {
        return "F";
    }
    if(old == "t")
    {
        return "while";
    }
    if(old == "u")
    {
        return "for";
    }
    if(old == "v")
    {
        return "num";
    }
    
    if(old == "w")
    {
        return "string";
    }
    
    if(old == "x")
    {
        return "bool";
    }
    
    string o = "><;()}{=,01";

    if(o.find(old[0]) != -1)
    {
        return old;
    }

}

void SyntaxTree::writeToFile(){

    prune();

    //find parent
    vector< pair< shared_ptr<node> , int > > open;
    pair<shared_ptr<node> , int > p;
    p.first = root;
    p.second = 0;
    int num;
    open.push_back(p);
    shared_ptr<node> temp;
    ofstream myfile;
    myfile.open ("syntaxTree.txt");

    while(open.empty() == false)
    {
        
        p.first = open.back().first;
        auto copy = p.first;
        num = open.back().second;

        open.pop_back();
      
        //display indents
        for(int i = 0 ; i<num ; i++ )
            myfile<<"| ";

     
         myfile<<"└─"<<p.first->ID<<": "<<p.first->name<<endl;

        for(auto it = copy->children.begin(); it != copy->children.end(); it++)
        {
            p.first = (*it);
            p.second = num+1;
            open.push_back(p);

        }
            
        

    }

    makeSymbolTable();
    
}

void SyntaxTree::prune(){
     //TODO: prune
    //to prune duplicates
    //for each node look if one of its children has the same name, if yes copy the child name to parent and delete child.
        //special 
            //userdefined
            //stringlit
            //integerlit

            //find parent
        string operators = ";<>,{}()=";
    vector<shared_ptr<node>> open;
    open.push_back(root);
    shared_ptr<node> temp;
    vector<shared_ptr<node>> children;

    while(open.empty() == false)
    {
        
        temp = open.back();
        open.pop_back();
    

        for(auto it = temp->children.begin(); it != temp->children.end(); it++)
        {
            //i should also push children to their own vector so ican comapre te
            open.push_back((*it));
            children.push_back((*it));

        }


       
        int count = 0;
        for(auto it = children.begin() ; it != children.end();it++)
        {
            if( (*it)->name == temp->name )
            {
                if(temp->children.size() == 1){
                    remove( temp->ID , count );
                    continue;
                }
                
            }
            else {if( (int)operators.find((*it)->name) != -1  )
            {
                remove( temp->ID , count );
                continue;
            }
            }

            if((*it)->name == "PROC_DEFS" && (*it)->children.size() == 0)
            {
                remove( temp->ID , count );
                continue;
            }


            count++;

        }

        

        children.clear();
            
        

    }
    
}

                        //parent   //index of child
void SyntaxTree::remove(int ID, int index){

    vector<shared_ptr<node>> open;
    open.push_back(root);
    shared_ptr<node> temp;

    while(open.empty() == false)
    {
        temp = open.back();
        open.pop_back();

        if(temp->ID == ID)
        {
            temp->children.erase(temp->children.begin() + index);
            return;
        }

    for(auto it = temp->children.begin(); it != temp->children.end(); it++)
        {
            
            open.push_back(*(it));

        }



}
}

void SyntaxTree::makeSymbolTable()
{
    //traverse through the tree and add a node to tree node that corresponds to the symbol table
     vector<shared_ptr<node>> open;
    open.push_back(root);
    shared_ptr<node> temp;

    while(open.empty() == false)
    {
        temp = open.back();
        open.pop_back();

        temp->tableNode = make_shared<symbolTableNode>();
        symbolTable.push_back(temp->tableNode);

        for(auto it = temp->children.begin(); it != temp->children.end(); it++)
        {
            open.push_back(*(it));

        }
    }
}