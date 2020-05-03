#include "parser/parser.hpp"

parser::parser(list<shared_ptr <token> > tokenList) {

    this->tokenList = tokenList;
}

parser::parser() {

}

parser::~parser() {

}

void parser::start()
{
    //here we need to input the grammar into the parser.
    addGrammar();
    initTable();

    //========================Calculating the first===========================================
    int NodeCount = 0;
    int numP = 47;//47
    int k = 0, kay = 0, ptr = -1, check = 0;
    char done[47], c;
    shared_ptr<nonTerminal> ANode = listNT[k];
    shared_ptr<nonTerminal> MyDisp;
    for(int i=0; i<listNT.size(); i++){
        MyDisp = listNT[i];
        for(int j=0; j<MyDisp->Productions.size(); j++){
            MyProductions.push_back(MyDisp->type+"="+MyDisp->Productions[j]);
        }
    }
    for(int i=0; i<numP; i++, NodeCount++){//counter for all nodes in total
        check = 0;
        if(NodeCount==ANode->Productions.size()){
            NodeCount=0;
            k++;
            ANode=listNT[k];
        }
        c = ANode->Productions[NodeCount].at(0);//type[0];
        TheFirst.clear();
        first(ANode,c,0,0,NodeCount);
    }
    //================================Calculating the follow====================================
    for(int i=0; i<listNT.size(); i++){        
        follow(listNT[i]);
    }
   
   
    
    /*for(int i=0;i<listNT.size();i++){
        MyDisp = listNT[i];
        cout<<MyDisp->type<<":";
        for(int j=0;j<MyDisp->followSet.size();j++)
            cout<<listNT[i]->followSet.at(j)<<"|";
        cout<<endl;
    }*/
    //PopulatPtable();

//////////////////////////////////////////////////////////////////////////////////////////////////////



    doMapping();
    Parse();

  
    if(syntaxError == false)
    {
    Tree->writeToFile();
    }
    else{
        cout<<"Syntax errors found, could not create AST"<<endl;
    }

}

void parser::first(shared_ptr<nonTerminal> MyNode, char c, int ProdPos, int RulePos, int nC){
    int numP = 47;
    string ffirst(MyNode->firstSet.begin(), MyNode->firstSet.end());

    if((!isupper(c)&&c!='%')){
        string sc(1, c);
        PopulatPtable(MyNode->Productions[nC], sc, MyNode->type);
    }
    if((!isupper(c)&&c!='%')&&(!((int)ffirst.find(c) >= 0))){//The case where you encounter a terminal
        MyNode->firstSet.push_back(c);//push onto first the terminal node
        return;
    }

    for(int j=0; j<numP; j++){
        string ffirst(MyNode->firstSet.begin(), MyNode->firstSet.end());
        if(MyProductions[j].at(0)==c){//if the current rule for the grammar(eg: E->MC;   if(E))
            if(MyProductions[j].at(2)=='#'){
                if((MyProductions[ProdPos].at(RulePos)=='%')&&(!((int)ffirst.find('#') >= 0))){
                    MyNode->firstSet.push_back('#');
                }else if((ProdPos!=0||RulePos!=0)){//if the current rule for the grammar(eg: E->MC;   if(!'\0'&&!E))
                    first(MyNode, MyProductions[ProdPos].at(RulePos), ProdPos, RulePos+1, nC);//call first of new non-terminal node
                }else if(!((int)ffirst.find('#') >= 0)){  
                    MyNode->firstSet.push_back('#');
                }
            }else if(!isupper((MyProductions[j].at(2)))){
                if((!((int)ffirst.find(MyProductions[j].at(2)) >= 0))){
                    MyNode->firstSet.push_back(MyProductions[j].at(2));
                }
                
                char t = MyProductions[j].at(2);
                if((!isupper(t)&&t!='%')){//&&(!((int)ffirst.find(t) >= 0))
                    string sc(1, t);
                    PopulatPtable(MyNode->Productions[nC], sc, MyNode->type);
                }
            }else{
                first(MyNode, MyProductions[j].at(2), j, 3, nC);//calc first for new non-terminal encountered
            }
        }
    }
}

void parser::follow( shared_ptr<nonTerminal> Current){
    //This function needs to find the follow for the current struct

    //if the current is our start symbol we add $ to the followSet
    if(Current->type == "S") // A 
    {   
        
        add(Current,'$');
    }

    //loop through all non terminals looking for current->type in their productions

    //loops through all non-Terminals
    for(auto it = listNT.begin() ; it != listNT.end() ; it++)
    {   
        //loops through all productions of individual non-terminal
        for(auto it2 = (*it)->Productions.begin() ; it2 != (*it)->Productions.end() ; it2++ )
        {
            //loops through the length of the individual Production
            for(int i = 0; i<(*it2).length();i++ )
            {
                string production = (*it2);
                producer = (*it);
                if( production[i] ==  Current->type[0] )
                {
                    if(production[i+1] != '%' )
                    {
                        // Calculate the first of the next 
                        // Non-Terminal in the production 
                        //followfirst() <- we probably need to pass this thing the struct with the ID == production[i+1] and the position ie (i)
                        //
                        //find struct with type = i+1 

                        //note i need to fix the case where this for-loop doesnt find anything, basically meaning that the next is a terminal
                        if(!isupper(production[i+1]))
                        {
                            
                            add(Current,production[i+1]);
                            continue;
                        }
                        for(auto it3 = listNT.begin() ; it3 != listNT.end() ; it3++)
                        {
                            if((*it3)->type[0] == production[i+1])
                            {
                                followfirst( Current ,(*it3) , production , i+1 );
                                break;
                            }
                        }
                    }
                    if( production[i+1] == '%' && Current->type != (*it)->type )
                    {
                        if((*it)->followSet.empty()==true)
                            follow((*it));
                        else{
                            for(int k = 0; k<(*it)->followSet.size();k++)
                                add(Current,(*it)->followSet[k]);
                        }
                    }
                }
            }
        }
    }
}

void parser::followfirst(shared_ptr<nonTerminal> Current, shared_ptr<nonTerminal> other , string production ,int pos){

    if( !isupper(production[pos]) )
    {
        add(Current,production[pos]);
    }
    else 
    {
        for(int i = 0 ; i<other->firstSet.size() ; i++)
        {
            if(other->firstSet[i] != '#')
            { 
                add(Current,other->firstSet[i]);
            }
            else
            {
                if(production[pos+1] == '%')
                {
                    if(producer->followSet.empty() == true)
                    {
                        follow(producer);
                    }
                    else{
                        for(int k = 0 ; k<producer->followSet.size();k++)
                            add(Current,producer->followSet[k]);
                    }
                }
                else
                {
                    //make other the struct with type pos++
                    //note i need to fix the case where this for-loop doesnt find anything, basically meaning that the next is a terminal
                    for(auto it3 = listNT.begin() ; it3 != listNT.end() ; it3++)
                    {
                        if((*it3)->type[0] == production[pos+1])
                        {
                            followfirst( Current ,(*it3) , production , ++pos );
                            break;
                        }
                    }
                }
                
            }
        }
    }
}

/*void parser::PopulatPtable(){

    shared_ptr<nonTerminal> MyCurrent;
    for(int i = 0; i<listNT.size(); i++){
        MyCurrent = listNT[i];
        string ffirst(MyCurrent->firstSet.begin(), MyCurrent->firstSet.end());
        for(int j = 0; j<MyCurrent->Productions.size();j++){
            for(int count=1; count<35; count++){
                if(((int)ffirst.find(ParseTable[count][0].at(0)) >= 0)){
                    ParseTable[count][i+1] = ParseTable[count][i+1]+MyCurrent->type+"="+MyCurrent->Productions[j];//to_string(i);
                }
            }
        }
    }
}*/
void parser::PopulatPtable(string P, string t, string Nt){
    bool check = false;
    for(int i = 1; i<35;i++){
        for(int j=1; j<20;j++){
            if(ParseTable[0][j] == Nt){
                if(ParseTable[i][0] == t){
                    size_t found = ParseTable[i][j].find(P);
                    if(found != string::npos){
                        check = true;
                    }
                    
                    if(!check){
                        ParseTable[i][j]=ParseTable[i][j]+P;//Nt+"|";//ParseTable[i][j]=ParseTable[i][j]+Nt+":"+P;
                    }
                }
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parser::addGrammar(){
  /*  //============================test data======================================
    shared_ptr<nonTerminal> S = make_shared<nonTerminal>();
    S->type = "S";
    S->Productions.push_back("ACB%");//CODE
    S->Productions.push_back("CbB%");//CODE;PROC_DEFS
    S->Productions.push_back("Ba%");
    //add to list
    listNT.push_back(S);

    shared_ptr<nonTerminal> A = make_shared<nonTerminal>();
    A->type = "A";
    A->Productions.push_back("da%");//CODE
    A->Productions.push_back("BC%");//CODE;PROC_DEFS
    //add to list
    listNT.push_back(A);

    shared_ptr<nonTerminal> B = make_shared<nonTerminal>();
    B->type = "B";
    B->Productions.push_back("g%");//CODE
    B->Productions.push_back("#%");//CODE;PROC_DEFS
    //add to list
    listNT.push_back(B);

    shared_ptr<nonTerminal> C = make_shared<nonTerminal>();
    C->type = "C";
    C->Productions.push_back("h%");//CODE
    C->Productions.push_back("#%");//CODE;PROC_DEFS
    //add to list
    listNT.push_back(C);
    //============================test data======================================
*/

    //PROG
    shared_ptr<nonTerminal> PROG = make_shared<nonTerminal>();
    PROG->type = "A";
    PROG->Productions.push_back("D%");//CODE
    PROG->Productions.push_back("D;B%");//CODE;PROC_DEFS
    //add to list
    listNT.push_back(PROG);


    //PROC_DEFS
    shared_ptr<nonTerminal> PROC_DEFS = make_shared<nonTerminal>();
    PROC_DEFS->type = "B";
    PROC_DEFS->Productions.push_back("C%");//PROC
    PROC_DEFS->Productions.push_back("CB%");//PROC&PROC_DEFS
    //add to list
    listNT.push_back(PROC_DEFS);

    //PROC
    shared_ptr<nonTerminal> PROC = make_shared<nonTerminal>();
    PROC->type = "C";
    PROC->Productions.push_back("ab{A}%");//proc userDefinedIdentifier{PROG}
    //add to list
    listNT.push_back(PROC);

    //CODE
    shared_ptr<nonTerminal> CODE = make_shared<nonTerminal>();
    CODE->type = "D";
    CODE->Productions.push_back("E%");//INSTR
    CODE->Productions.push_back("E;D%");//INSTR;CODE
    //add to list
    listNT.push_back(CODE);

    //INSTR
    shared_ptr<nonTerminal> INSTR = make_shared<nonTerminal>();
    INSTR->type = "E";
    INSTR->Productions.push_back("c%");//halt
    INSTR->Productions.push_back("F%");//DECL
    INSTR->Productions.push_back("G%");//IO
    INSTR->Productions.push_back("H%");//CALL
    INSTR->Productions.push_back("I%");//ASSIGN
    INSTR->Productions.push_back("J%");//COND_BRANCH
    INSTR->Productions.push_back("K%");//COND_LOOP
    //add to list
    listNT.push_back(INSTR);

    //DECL 
    shared_ptr<nonTerminal> DECL = make_shared<nonTerminal>();
    DECL->type = "F";
    DECL->Productions.push_back("LM%");//TYPE&NAME
    DECL->Productions.push_back("LM;F%");//TYPE&NAME;DECL
    //add to list
    listNT.push_back(DECL);

    //IO
    shared_ptr<nonTerminal> IO = make_shared<nonTerminal>();
    IO->type = "G";
    IO->Productions.push_back("d(N)%");//input(VAR)
    IO->Productions.push_back("e(N)%");//output(VAR)
    //add to list
    listNT.push_back(IO);

    //CALL
    shared_ptr<nonTerminal> CALL = make_shared<nonTerminal>();
    CALL->type = "H";
    CALL->Productions.push_back("b%");//userDefinedIdentifier
    //add to list
    listNT.push_back(CALL);

    //ASSIGN
    shared_ptr<nonTerminal> ASSIGN = make_shared<nonTerminal>();
    ASSIGN->type = "I";
    ASSIGN->Productions.push_back("N=f%");//VAR=stringLiteral
    ASSIGN->Productions.push_back("N=N%");//VAR=VAR
    ASSIGN->Productions.push_back("N=O%");//VAR=NUMEXPR
    ASSIGN->Productions.push_back("N=Q%");//VAR=BOOL
    //add to list
    listNT.push_back(ASSIGN);

    //COND_BRANCH
    shared_ptr<nonTerminal> COND_BRANCH = make_shared<nonTerminal>();
    COND_BRANCH->type = "J";
    COND_BRANCH->Productions.push_back("k(Q)l{D}%");//if(BOOL)then{CODE}
    COND_BRANCH->Productions.push_back("k(Q)l{D}m{D}%");//if(BOOL)then{CODE}else{CODE}
    //add to list
    listNT.push_back(COND_BRANCH);

    //COND_LOOP
    shared_ptr<nonTerminal> COND_LOOP = make_shared<nonTerminal>();
    COND_LOOP->type = "K";
    COND_LOOP->Productions.push_back("t(Q){D}%");//while(BOOL){CODE}
    COND_LOOP->Productions.push_back("u(N=0;N<N;N=h(N,1)){D}%");//for(VAR=0;VAR<VAR;VAR=add(VAR,1)){CODE}
    //add to list
    listNT.push_back(COND_LOOP);

    //TYPE 
    shared_ptr<nonTerminal> TYPE = make_shared<nonTerminal>();
    TYPE->type = "L";
    TYPE->Productions.push_back("v%");//num
    TYPE->Productions.push_back("w%");//string
    TYPE->Productions.push_back("x%");//bool
    //add to list
    listNT.push_back(TYPE);

    //NAME
    shared_ptr<nonTerminal> NAME = make_shared<nonTerminal>();
    NAME->type = "M";
    NAME->Productions.push_back("b%");//userDefinedIdentifier
    //add to list
    listNT.push_back(NAME);

    //VAR
    shared_ptr<nonTerminal> VAR = make_shared<nonTerminal>();
    VAR->type = "N";
    VAR->Productions.push_back("b%");//userDefinedIdentifier
    //add to list
    listNT.push_back(VAR);

    //NUMEXPR
    shared_ptr<nonTerminal> NUMEXPR = make_shared<nonTerminal>();
    NUMEXPR->type = "O";
    NUMEXPR->Productions.push_back("N%");//VAR
    NUMEXPR->Productions.push_back("g%");//integerLiteral
    NUMEXPR->Productions.push_back("P%");//CALC
    //add to list
    listNT.push_back(NUMEXPR);
    
    //CALC
    shared_ptr<nonTerminal> CALC = make_shared<nonTerminal>();
    CALC->type = "P";
    CALC->Productions.push_back("h(O,O)%");//add(NUMEXPR,NUMEXPR)
    CALC->Productions.push_back("i(O,O)%");//sub(NUMEXPR,NUMEXPR)
    CALC->Productions.push_back("j(O,O)%");//mult(NUMEXPR,NUMEXPR)
    //add to list
    listNT.push_back(CALC);

    //BOOL
    shared_ptr<nonTerminal> BOOL = make_shared<nonTerminal>();
    BOOL->type = "Q";
    BOOL->Productions.push_back("n(N,N)%");//eq(VAR,VAR)
    BOOL->Productions.push_back("(N<N)%");//(VAR<VAR)
    BOOL->Productions.push_back("(N>N)%");//(VAR>VAR)
    BOOL->Productions.push_back("oQ%");//not BOOL
    BOOL->Productions.push_back("p(Q,Q)%");//and(BOOL,BOOL)
    BOOL->Productions.push_back("q(Q,Q)%");//or(BOOL,BOOL)
    BOOL->Productions.push_back("r%");//T
    BOOL->Productions.push_back("s%");//F
    BOOL->Productions.push_back("N%");//VAR
    //add to list
    listNT.push_back(BOOL);

    return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string parser::map(string original){
    string mapped = "";
    if(original == "tok_proc"){
        mapped = "a";
    }else if(original == "var"){//user defined 
        mapped = "b";
    }else if(original == "tok_halt"){
        mapped = "c";
    }else if(original == "tok_input"){
        mapped = "d";
    }else if(original == "tok_output"){
        mapped = "e";
    }else if(original == "tok_String_literal"){
        mapped = "f";
    }else if(original == "tok_int"){//user defined integer
        mapped = "g";
    }else if(original == "tok_add"){
        mapped = "h";
    }else if(original == "tok_sub"){
        mapped = "i";
    }else if(original == "tok_mult"){
        mapped = "j";
    }else if(original == "tok_if"){
        mapped = "k";
    }else if(original == "tok_then"){
        mapped = "l";
    }else if(original == "tok_else"){
        mapped = "m";
    }else if(original == "tok_eq"){
        mapped = "n";
    }else if(original == "tok_not"){
        mapped = "o";
    }else if(original == "tok_and"){
        mapped = "p";
    }else if(original == "tok_or"){
        mapped = "q";
    }else if(original == "tok_T"){
        mapped = "r";
    }else if(original == "tok_F"){
        mapped = "s";
    }else if(original == "tok_while"){
        mapped = "t";
    }else if(original == "tok_for"){
        mapped = "u";
    }else if(original == "tok_num"){
        mapped = "v";
    }else if(original == "tok_string"){
        mapped = "w";
    }else if(original == "tok_bool"){
        mapped = "x";
    }else if(original == "tok_lthan"){
        mapped = "<";
    }else if(original == "tok_gthan"){
        mapped = ">";
    }else if(original == "#"){
        mapped = "#";
    }else if(original == "tok_oparen"){
        mapped = "(";
    }else if(original == "tok_cparen"){
        mapped = ")";
    }else if(original == "tok_obrace"){
        mapped = "{";
    }else if(original == "tok_cbrace"){
        mapped = "}";
    }else if(original == "tok_equal"){
        mapped = "=";
    }else if(original == "tok_comma"){
        mapped = ",";
    }else if(original == "tok_semicolon"){
        mapped = ";";
    }else if(original == "0"){
        mapped = "0";
    }else if(original == "1"){
        mapped = "1";
    }
    return mapped;
}


void parser::add(shared_ptr<nonTerminal> Current, char c)
{
    bool contains =false;
    for (int i =0 ; i< Current->followSet.size() ; i++)
    {
        if(Current->followSet[i] == c)
        {
            contains=true;
            break;
        }
    }

    if(contains == false)
        Current->followSet.push_back(c);

        
}

void parser::initTable(){
    char myC = 'A';
    for(int i = 0; i<19; i++){
        string s(1, myC+i);
        ParseTable[0][i+1]=s;
    }
    myC='a';
    for(int i = 0; i<24; i++){
        string s(1, myC+i);
        ParseTable[i+1][0]=s;
    }
    ParseTable[25][0]='<';
    ParseTable[26][0]='>';
    ParseTable[27][0]='(';
    ParseTable[28][0]=')';
    ParseTable[29][0]='{';
    ParseTable[30][0]='}';
    ParseTable[31][0]='=';
    ParseTable[32][0]=',';
    ParseTable[33][0]=';';
    ParseTable[34][0]='$';
}

void parser::doMapping()
{
    for(auto it = tokenList.begin() ; it != tokenList.end() ; it++ )
    {
        //makes our tokenList contain the new mapping.
        (*it)->token_type = map((*it)->token_type);    
    }

    
}

void parser::Parse()
{
    pair<string,int> p;
    int currentParentID;
    Tree = make_shared<SyntaxTree>();
    auto it = tokenList.begin();

    //fuck i need to make the stack store pairs, string,int the int will be its parents ID
   
    p.first = "$";
    p.second = -1;
    stack.push_back(p); // initail item on the stack.

    currentParentID=Tree->createTree("A");
    p.first = "A";
    p.second = currentParentID;
    stack.push_back(p);
    string top;
    
        //this loop goes through all tokens
    while(it != tokenList.end())
    {
        if(syntaxError == true)
        {
            cout<<"Syntax errors found could not continue parsing, Please fix errors"<<endl;
            break;
        }
        top = stack[stack.size() - 1 ].first;
        currentParentID = stack[stack.size() - 1 ].second;
        stack.pop_back();
//================if we reach end of stack======================================
        if(top == "$")
        {
            //if we get here we are at the end of parse
            break;
        }
//================if we have a terminal===========================================
        if( !isupper(top[0]) )
        {
            if( top == (*it)->token_type || ( top == "0" && (*it)->token_type == "g") || ( top == "1" && (*it)->token_type == "g") )
                {
                    //terminal match
                    Tree->addNode(currentParentID,(*it)->token_str,false);
                    it++;
                    continue;
                }
            else
            {
                
                cout<<"syntax error: "<<"[line: "<<(*it)->MyLine<<" col: "<<(*it)->MyCol<<"] " << "Expected: "<<top<<" , but found: "<<(*it)->token_type<<endl;
                it++;
                syntaxError = true;
                
            }
            
                
        }
//==========if we have a non-terminal===============================================  
    else{
        int row;
        //parsetable[35][20]
       for(int i = 0 ; i<35 ; i++)
       {
           if(ParseTable[i][0] == (*it)->token_type )
           {
               row = i;
           }
       }

       int col;

       for(int i = 0 ; i<20 ; i++)
       {
           if(ParseTable[0][i] == top )
           {
               col = i;
           }
       }


//===============if statements ====================================================

    if(ParseTable[0][col] == "A")
    {
        progRule(it,row,col,currentParentID);
        continue;
    }

    if(ParseTable[0][col] == "B")
    {
        procRule(it,row,col,currentParentID);
        continue;
    }

    if(ParseTable[0][col] == "F")
    {
        DECLRule(it,row,col,currentParentID);
        continue;
    }

    if(ParseTable[0][col] == "D")
    {
        codeRule(it,row,col,currentParentID);
        continue;
    }

//=========================================================================================

    //if i have more than one rule , i need to determine which rule to use.
            
        //first need to split all rules into vector<string> 
        string ruleList = ParseTable[row][col];
        vector<string> rules;
        string temp;
        auto copy = it;

            int n = count(ruleList.begin(), ruleList.end(), '%');

            if(n>=2)
            {
                for(int i=0 ; i<n ; i++)
                {
                rules.push_back( ruleList.substr(0,ruleList.find_first_of('%')) );
                ruleList.erase(0,ruleList.find_first_of('%')+1);

                }

                //test if we have assign or call
                
                if(rules[0] == "H")
                {
                    if( (*++copy)->token_type == "=" )
                    {
                        //rule 2
                        p.second = Tree->addNode(currentParentID,rules[1],true);
                        p.first = rules[1];
                        stack.push_back(p);
                        continue;

                    }

                    else{
                        
                        p.second = Tree->addNode(currentParentID,rules[0],true);
                        p.first = rules[0];
                        stack.push_back(p);
                        temp="";
                        continue;

                    }
                }

                //test what type of assign we have
                ++copy;
                ++copy;
                string test = (*copy)->token_type;
                if(rules[0] == "N=f")
                {
                    if( (*copy)->token_type == "f")
                    {
                        //rule 0
                       for(int k = 2 ; k>-1 ; --k)
                         {
                             temp.push_back(rules[0][k]);
                             p.second = Tree->addNode(currentParentID,temp,true);
                             p.first = temp;
                             stack.push_back(p);
                             temp="";
                            }
                            continue;
                    }
                    if((*copy)->token_type == "b")
                    {
                         //rule 1
                       for(int k = 2 ; k>-1 ; --k)
                         {
                             temp.push_back(rules[1][k]);
                             p.second = Tree->addNode(currentParentID,temp,true);
                             p.first = temp;
                             stack.push_back(p);
                             temp="";
                            }
                            continue;
                    }
                      if((*copy)->token_type == "g" || (*copy)->token_type == "h" || (*copy)->token_type == "i" || (*copy)->token_type == "j" )
                    {
                        //rule 2
                       for(int k = 2 ; k>-1 ; --k)
                         {
                             temp.push_back(rules[2][k]);
                             p.second = Tree->addNode(currentParentID,temp,true);
                             p.first = temp;
                             stack.push_back(p);
                             temp="";
                            }
                            continue;
                    }
                      if((*copy)->token_type == "n" || (*copy)->token_type == "(" || (*copy)->token_type == "p" || (*copy)->token_type == "q" || (*copy)->token_type == "o" || (*copy)->token_type == "r" || (*copy)->token_type == "s")
                    {
                        //rule 3
                        for(int k = 2 ; k>-1 ; --k)
                         {
                             temp.push_back(rules[3][k]);
                             p.second = Tree->addNode(currentParentID,temp,true);
                             p.first = temp;
                             stack.push_back(p);
                             temp="";
                            }
                            continue;
                    }



                    //log error
                   
                cout<<"syntax error: "<<"[line: "<<(*it)->MyLine<<" col: "<<(*it)->MyCol<<"] Assignment statement incorrect"<<endl;
                it++;
                syntaxError = true;
                continue;


                }

                
               

                if(rules[0][0] == 'k')
                {
                     auto copy = it;
                     int counter=0;
                     bool stop = false;

                    while(stop == false)
                    {
                    copy++;

                    if(copy == tokenList.end())
                     {
                            for(int k = rules[1].length() -1 ; k>-1 ; --k)
                {
                    temp.push_back(rules[1][k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                }
                continue;
                        }

                        if((*copy)->token_type == "{")
                        {
                            counter++;
                        }

                if((*copy)->token_type == "}")
                    {
                        counter--;
                        if(counter==0)
                            {
                                stop = true;
                            }
                    }
                }

                if((*++copy)->token_type == "m")
                {
                      for(int k = rules[1].length() -1 ; k>-1 ; --k)
                {
                    temp.push_back(rules[1][k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                }
                continue;
                }
                else{

                    for(int k = rules[0].length() -1 ; k>-1 ; --k)
                {
                    temp.push_back(rules[0][k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                }
                continue;

            }



                }

                copy = it;
                //test case where we have N<N || N>N
                if(rules[0] == "(N<N)")
                {
                    copy++;
                    copy++;
                  if((*copy)->token_type == "<")
                  {
                      for(int k = rules[0].length() -1 ; k>-1 ; --k)
                    {
                    temp.push_back(rules[0][k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                    }
                continue;

                  }
                  else{
                       for(int k = rules[1].length() -1 ; k>-1 ; --k)
                    {
                    temp.push_back(rules[1][k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                    }
                continue;

                  }
                    
                }




            }
        else{
            for(int i = ruleList.length() -2 ; i>-1 ; i--)
            {
            temp.push_back(ruleList[i]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
            }
        }
            
            //if there is more than 1 rule 
                //check which function to use 
                //in choosen function decide which rule to use.
                //continue

    }
        


    }






}

void parser::progRule(auto it,int row,int col ,int currentParentID)
{   
    
    //in this function i need to decide which PROG rule to use.
    pair<string,int> p;
    string rules = ParseTable[row][col];

      string rule1 = rules.substr(0,rules.find_first_of('%'));
      int k = rules.find_first_of('%')+1;
      string rule2 = rules.substr(k,rules.find_last_of('%') - k);

      if(rules == "")
      {
          cout<<"syntax error: "<<"[line: "<<(*it)->MyLine<<" col: "<<(*it)->MyCol<<"] Expected INSTR but found: "<<(*it)->token_type<<endl;
          syntaxError = true;
      }

      //put rule onto stack
      string temp;
    //===================THIS is the case when prog is called within a proc=========================
    
    //if --copy == "{"
    //then, we need to find this proc's closing bracket
    //if we dont find any proc_defs on the way we use small rule.
   
    if(it != tokenList.begin())
    {
    auto copy = it;
    if((*--copy)->token_type == "{")
    {
    ++copy;
    bool stop = false;
    int counter = 0;
    bool found = false;
    while(stop == false)
    {
        copy++;

                if(copy == tokenList.end())
                {
                    //use long rule
                    for(int k = rule2.length() -1 ; k>-1 ; --k)
          {
            temp.push_back(rule2[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
          }
          return ;

                }

                if((*copy)->token_type == "a")
                {
                    found = true;
                }

                if((*copy)->token_type == "{")
                {
                    counter++;
                }
                if((*copy)->token_type == "}")
                {
                    if(counter == 0)
                        stop=true;
                    else counter--;
                        
                }

    }

    if(found == true)
    {
        for(int k = rule2.length() -1 ; k>-1 ; --k)
          {
            temp.push_back(rule2[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
          }
          return ;

    }
    else{
        for(int k = rule1.length() -1 ; k>-1 ; --k)
          {
          temp.push_back(rule1[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
          }
          return ;


    }



    }
}



    //============================================================================================= 
      //===========THIS is case when regular prog is called====================
        bool r2 = false;
      for(it ; it != tokenList.end() ; it++)
      {
          if( (*it)->token_type == "a" )
          {
              r2 =true;
          }
      }

      if(r2 == true)
      {
          for(int k = rule2.length() -1 ; k>-1 ; --k)
          {
            temp.push_back(rule2[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
          }

      }
      else{
          for(int k = rule1.length() -1 ; k>-1 ; --k)
          {
          temp.push_back(rule1[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
          }

      }
      //=======================================================================

    }

void parser::procRule(auto it,int row,int col ,int currentParentID){

     //in this function i need to decide which proc rule to use.
    pair<string,int> p;
    string rules = ParseTable[row][col];

      string rule1 = rules.substr(0,rules.find_first_of('%'));
      int k = rules.find_first_of('%')+1;
      string rule2 = rules.substr(k,rules.find_last_of('%') - k);

      //put rule onto stack
      string temp;

      if(rules == "")
      {
          cout<<"syntax error: "<<"[line: "<<(*it)->MyLine<<" col: "<<(*it)->MyCol<<"] Expected proc but found: "<<(*it)->token_type<<endl;
          syntaxError = true;
          return;
      }
        
      //put for loop from it till tokens.end()
      // if any it->tokens_str = proc
      //use rule 2
      //else
      //use rule 1

      
      /*  bool r2 = false;
        it++;
      for(it ; it != tokenList.end() ; it++)
      {
          if( (*it)->token_type == "a" )
          {
              r2 =true;
          }
      }*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++=
    auto copy = it;
    bool stop = false;
    int counter = 0;
    bool found = false;
    while(stop == false)
    {
        copy++;

                if(copy == tokenList.end())
                {
                    //use long rule
                    for(int k = rule2.length() -1 ; k>-1 ; --k)
                    {
                    temp.push_back(rule2[k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                    }
                    return ;

                }

                
                if((*copy)->token_type == "{")
                {
                    counter++;
                }
                if((*copy)->token_type == "}")
                {
                    if(counter == 0){
                        stop=true;
                        
                    }
                    else counter--;

                    if(counter == 0)
                        stop=true;
                        
                }

    }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
        if(++copy == tokenList.end())
    {
          for(int k = rule1.length() -1 ; k>-1 ; --k)
        {
          temp.push_back(rule1[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
        }
        return;

      }

      
       
      if((*copy)->token_type == "a")
      {
          for(int k = rule2.length() -1 ; k>-1 ; --k)
        {
            temp.push_back(rule2[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
        }

      }
      else{
           for(int k = rule1.length() -1 ; k>-1 ; --k)
        {
          temp.push_back(rule1[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
        }

      }
      


}



void parser::DECLRule(auto it,int row,int col ,int currentParentID){

    //in this function i need to decide which DECL rule to use.
    pair<string,int> p;
    string rules = ParseTable[row][col];

      string rule1 = rules.substr(0,rules.find_first_of('%'));
      int k = rules.find_first_of('%')+1;
      string rule2 = rules.substr(k,rules.find_last_of('%') - k);

      //put rule onto stack
      string temp;

    //here i need to decide which DECL rule to use.

    it++;
    it++;
    it++;
    // if i can find a DECL keyword in next statement then use long rule.
    string check = (*it)->token_type;
    if((*it)->token_type == "v" || (*it)->token_type == "w" || (*it)->token_type == "x" )
    {
        for(int k = rule2.length() -1 ; k>-1 ; --k)
        {
            temp.push_back(rule2[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
          }

    }
    else{
        for(int k = rule1.length() -1 ; k>-1 ; --k)
        {
            temp.push_back(rule1[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
          }

    }


}

void  parser::codeRule(auto it,int row,int col ,int currentParentID){
     //in this function i need to decide which code rule to use.
    pair<string,int> p;
    string rules = ParseTable[row][col];

      string rule1 = rules.substr(0,rules.find_first_of('%'));
      int k = rules.find_first_of('%')+1;
      string rule2 = rules.substr(k,rules.find_last_of('%') - k);
      
      //put rule onto stack
      string temp;


    //here i need to decide which instr rule to use
      
    int counter = 0;
    bool stop = false;

       if((*it)->token_type == "t" || (*it)->token_type == "u" )
        {
            while(stop == false)
            {
                it++;

                if(it == tokenList.end())
                {
                    //use long rule
                    for(int k = rule2.length() -1 ; k>-1 ; --k)
                {
                    temp.push_back(rule2[k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                }
                return;
                }

                if((*it)->token_type == "{")
                {
                    counter++;
                }
                if((*it)->token_type == "}")
                {
                    if(counter == 0)
                        stop=true;
                    else counter--;

                    if(counter == 0)
                        stop=true;
                        
                }

            }
            ++it;

            if(it == tokenList.end())
            {
                    temp.push_back(rule1[0]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                    return;

            }



            if((*it)->token_type == ";" && (*++it)->token_type != "a")
            {
                //use long
               for(int k = rule2.length() -1 ; k>-1 ; --k)
                {
                    temp.push_back(rule2[k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                }
                return;
            }
            else{
                    temp.push_back(rule1[0]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                    return;
            }
        



        }
       
        //okay here i need to determine where the if statement ends
            //then check if theres a semi colon and next is not proc
            
     if((*it)->token_type == "k")
        {

            //first determine if the statement we working with has an else statement
            while(stop == false)
            {
                it++;

                if(it == tokenList.end())
                {
                    //use long rule
                }

                if((*it)->token_type == "{")
                {
                    counter++;
                }

                if((*it)->token_type == "}")
                {
                    counter--;
                    if(counter==0)
                    {
                        stop = true;
                    }
                }

            }


            stop = false;
            counter=0;
            if((*++it)->token_type == "m")
            {
                //find the end of else
                while(stop == false)
                {
                    it++;

                if(it == tokenList.end())
                {
                    //use long rule
                     for(int k = rule2.length() -1 ; k>-1 ; --k)
                {
                    temp.push_back(rule2[k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                }
                return;
                }

                if((*it)->token_type == "{")
                {
                    counter++;
                }

                if((*it)->token_type == "}")
                {
                    counter--;
                    if(counter==0)
                    {
                        stop = true;
                    }
                }

                }

                if(++it == tokenList.end())
                {
                    temp.push_back(rule1[0]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                    return;

                }

                --it;
                if((*++it)->token_type == ";")
                {
                for(int k = rule2.length() -1 ; k>-1 ; --k)
                {
                    temp.push_back(rule2[k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                }
                return;
                }
            else{

                    temp.push_back(rule1[0]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                    return;
            }
            

            }
            else{
                --it;
               if((*++it)->token_type == ";")
                {
                for(int k = rule2.length() -1 ; k>-1 ; --k)
                {
                    temp.push_back(rule2[k]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                }
                return;
                }
            else{

                    temp.push_back(rule1[0]);
                    p.second = Tree->addNode(currentParentID,temp,true);
                    p.first = temp;
                    stack.push_back(p);
                    temp="";
                    return;
            }
            
            }
            
        }





        //other just look for semi colon then u know there is another statement coming
//===================================================================================================
        string Z = ";";
        bool r2 = false;
        auto copy = it;
        bool other = false;
        

        //======================================================================
        

       while(r2 == false)
        {
            it++;
           
            if(it == tokenList.end())
                {
                    for(int k = rule1.length() -1 ; k>-1 ; --k)
                    {
                        temp.push_back(rule1[k]);
                        p.second = Tree->addNode(currentParentID,temp,true);
                        p.first = temp;
                        stack.push_back(p);
                        temp="";
                    }
                    return;
                }

                if( (*it)->token_type == ";" )
                    {
                        r2 =true;
                        copy = it;
                        break;
                    }
                    if((*it)->token_type == "}" || (*it)->token_type == "{")
                    {
                        other = true;
                        break;
                    }



        }

         
//============================================================================================
    auto c = copy;
    c++;
    if(c == tokenList.end())
    {
        for(int k = rule1.length() -1 ; k>-1 ; --k)
        {
          temp.push_back(rule1[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
        }
        return;
    }

      string test = (*c)->token_type;

      if(r2 == true && (*++copy)->token_type != "a" && other == false)
      {
          for(int k = rule2.length() -1 ; k>-1 ; --k)
        {
            temp.push_back(rule2[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
        }

      }
      else{
          for(int k = rule1.length() -1 ; k>-1 ; --k)
        {
          temp.push_back(rule1[k]);
            p.second = Tree->addNode(currentParentID,temp,true);
            p.first = temp;
            stack.push_back(p);
            temp="";
        }

      }

}


