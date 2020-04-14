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
    cout<<"First: "<<endl;
    for(int i=0;i<listNT.size();i++){
        MyDisp = listNT[i];
        cout<<MyDisp->type<<":";
        for(int j=0;j<MyDisp->firstSet.size();j++)
            cout<<listNT[i]->firstSet.at(j)<<"|";
        cout<<endl;
    }
    cout<<"Follow: "<<endl;
    /*for(int i=0;i<listNT.size();i++){
        MyDisp = listNT[i];
        cout<<MyDisp->type<<":";
        for(int j=0;j<MyDisp->followSet.size();j++)
            cout<<listNT[i]->followSet.at(j)<<"|";
        cout<<endl;
    }*/
    //PopulatPtable();
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
            if(!isupper((MyProductions[j].at(2)))){
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
    ASSIGN->Productions.push_back("N=R%");//VAR=BOOL
    //add to list
    listNT.push_back(ASSIGN);

    //COND_BRANCH
    shared_ptr<nonTerminal> COND_BRANCH = make_shared<nonTerminal>();
    COND_BRANCH->type = "J";
    COND_BRANCH->Productions.push_back("k(R)l{D}%");//if(BOOL)then{CODE}
    COND_BRANCH->Productions.push_back("k(R)l{D}m{D}%");//if(BOOL)then{CODE}else{CODE}
    //add to list
    listNT.push_back(COND_BRANCH);

    //COND_LOOP
    shared_ptr<nonTerminal> COND_LOOP = make_shared<nonTerminal>();
    COND_LOOP->type = "K";
    COND_LOOP->Productions.push_back("t(R){D}%");//while(BOOL){CODE}
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
    BOOL->Productions.push_back("oR%");//not BOOL
    BOOL->Productions.push_back("p(R,R)%");//and(BOOL,BOOL)
    BOOL->Productions.push_back("q(R,R)%");//or(BOOL,BOOL)
    BOOL->Productions.push_back("r%");//T
    BOOL->Productions.push_back("s%");//F
    BOOL->Productions.push_back("N%");//VAR
    //add to list
    listNT.push_back(BOOL);

    return;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//==========================================Mapping===============================================
//Mapping Non-terminals to characters
//==========================================Mapping===============================================
//A=>PROG
//B=>PROC_DEFS
//C=>PROC
//D=>CODE
//E=>INSTR
//F=>DECL
//G=>IO
//H=>CALL
//I=>ASSIGN
//J=>COND_BRANCH
//K=>COND_LOOP
//L=>TYPE
//M=>NAME
//N=>VAR
//O=>NUMEXPR
//P=>CALC
//Q=>BOOL
//R=>
//S=>
//T=>
//U=>
//V=>
//W=>
//X=>
//Y=>
//Z=>
//==========================================Mapping===============================================
//Mapping terminals to characters
//==========================================Mapping==============================================
//a=>proc
//b=>userDefinedIdentifier  //this is userdefined and therefore isn't a set in stone string
//c=>halt
//d=>input
//e=>output
//f=>stringLiteral  //this is userdefined and therefore isn't a set in stone string
//g=>integerLiteral  //this is userdefined and therefore isn't a set in stone string
//h=>add
//i=>sub
//j=>mult
//k=>if
//l=>then
//m=>else
//n=>eq
//o=>not
//p=>and
//q=>or
//r=>T
//s=>F
//t=>while
//u=>for
//v=>num
//w=>string
//x=>bool
//y=>
//z=>
//All operators
//< > # ( ) { } = , ;  /*space not included*/
//Some integers
//0 1

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