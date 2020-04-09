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

    //========================Calculating the first===========================================
    int NodeCount = 0;
    int k = 0, kay = 0, ptr = -1, check = 0;
    char done[47], c;
    shared_ptr<nonTerminal> ANode = listNT[k];
    for(int i=0; i<47; i++, NodeCount++){//counter for all nodes in total
        if(NodeCount==ANode->Productions.size()){
            NodeCount=0;
            k++;
            ANode=listNT[k];
        }
        c = ANode->type[0];
        for(kay=0; kay<=ptr; kay++){
            if(c==done[kay]){check=1;}
        }
        if(check==1){
            continue;
        }
        first(ANode,c,0,0);
        ptr++;
        done[ptr] = c;
    }
    //========================Calculating the first===========================================
    shared_ptr<nonTerminal> MyDisp;
    for(int i=0; i<listNT.size(); i++){
        MyDisp = listNT[i];
        cout<<MyDisp->type<<":";
        for(int j=0; j<MyDisp->firstSet.size(); j++){
            cout<<MyDisp->firstSet[j]<<",";
        }
        cout<<endl;
    }





}

void parser::first(shared_ptr<nonTerminal> MyNode, char c, int ProdPos, int RulePos){
    int cProd = 0;//will be the number of productions in the struct currently
    int count2 = 0;//counter for ListNT
    shared_ptr<nonTerminal> ANode = listNT[count2];//ANode is used to increment through all the non-terminals

    if(!isupper(c)){//The case where you encounter a terminal
        MyNode->firstSet.push_back(c);//push onto first the terminal node
    }

    for(int j=0; j<47; j++, cProd++){
        if(cProd==ANode->Productions.size()){
            cProd=0;
            count2++;
            ANode=listNT[count2];
        }
        if(ANode->type[0]==c){//if the current rule for the grammar(eg: E->MC;   if(E))
            if(ANode->Productions[cProd].at(0)=='#'){
                if(ANode->Productions[ProdPos].at(RulePos)=='\0'){
                    MyNode->firstSet.push_back('#');
                }else if((ProdPos!=0||RulePos!=0)){//if the current rule for the grammar(eg: E->MC;   if(!'\0'&&!E))
                    first(ANode, MyNode->Productions[ProdPos].at(RulePos), ProdPos, RulePos+1);//call first of new non-terminal node
                }else{  
                    MyNode->firstSet.push_back('#');
                }
            }else if(!isupper(ANode->Productions[cProd].at(0))){
                MyNode->firstSet.push_back(ANode->Productions[cProd].at(0));
            }else{
                first(ANode, ANode->Productions[cProd].at(0), cProd, 1);//calc first for new non-terminal encountered
            }
        }
    }
}

void parser::follow(){
    
}














































///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parser::addGrammar(){

    //PROG
    shared_ptr<nonTerminal> PROG = make_shared<nonTerminal>();
    PROG->type = "A";
    PROG->Productions.push_back("D");//CODE
    PROG->Productions.push_back("D;B");//CODE;PROC_DEFS
    //add to list
    listNT.push_back(PROG);


    //CODE
    shared_ptr<nonTerminal> CODE = make_shared<nonTerminal>();
    CODE->type = "D";
    CODE->Productions.push_back("E");//INSTR
    CODE->Productions.push_back("E;D");//INSTR;CODE
    //add to list
    listNT.push_back(CODE);

    //PROC_DEFS
    shared_ptr<nonTerminal> PROC_DEFS = make_shared<nonTerminal>();
    PROC_DEFS->type = "B";
    PROC_DEFS->Productions.push_back("C");//PROC
    PROC_DEFS->Productions.push_back("CB");//PROC&PROC_DEFS
    //add to list
    listNT.push_back(PROC_DEFS);

    //PROC
    shared_ptr<nonTerminal> PROC = make_shared<nonTerminal>();
    PROC->type = "C";
    PROC->Productions.push_back("ab{A}");//proc userDefinedIdentifier{PROG}
    //add to list
    listNT.push_back(PROC);

    //INSTR
    shared_ptr<nonTerminal> INSTR = make_shared<nonTerminal>();
    INSTR->type = "E";
    INSTR->Productions.push_back("c");//halt
    INSTR->Productions.push_back("F");//DECL
    INSTR->Productions.push_back("G");//IO
    INSTR->Productions.push_back("H");//CALL
    INSTR->Productions.push_back("I");//ASSIGN
    INSTR->Productions.push_back("J");//COND_BRANCH
    INSTR->Productions.push_back("K");//COND_LOOP
    //add to list
    listNT.push_back(INSTR);


    //IO
    shared_ptr<nonTerminal> IO = make_shared<nonTerminal>();
    IO->type = "G";
    IO->Productions.push_back("d(N)");//input(VAR)
    IO->Productions.push_back("e(N)");//output(VAR)
    //add to list
    listNT.push_back(IO);

    //CALL
    shared_ptr<nonTerminal> CALL = make_shared<nonTerminal>();
    CALL->type = "H";
    CALL->Productions.push_back("b");//userDefinedIdentifier
    //add to list
    listNT.push_back(CALL);

    //DECL 
    shared_ptr<nonTerminal> DECL = make_shared<nonTerminal>();
    DECL->type = "F";
    DECL->Productions.push_back("LM");//TYPE&NAME
    DECL->Productions.push_back("LM;F");//TYPE&NAME;DECL
    //add to list
    listNT.push_back(DECL);

    //TYPE 
    shared_ptr<nonTerminal> TYPE = make_shared<nonTerminal>();
    TYPE->type = "L";
    TYPE->Productions.push_back("v");//num
    TYPE->Productions.push_back("w");//string
    TYPE->Productions.push_back("x");//bool
    //add to list
    listNT.push_back(TYPE);

    //NAME
    shared_ptr<nonTerminal> NAME = make_shared<nonTerminal>();
    NAME->type = "M";
    NAME->Productions.push_back("b");//userDefinedIdentifier
    //add to list
    listNT.push_back(NAME);

    //VAR
    shared_ptr<nonTerminal> VAR = make_shared<nonTerminal>();
    VAR->type = "N";
    VAR->Productions.push_back("b");//userDefinedIdentifier
    //add to list
    listNT.push_back(VAR);

    //ASSIGN
    shared_ptr<nonTerminal> ASSIGN = make_shared<nonTerminal>();
    ASSIGN->type = "I";
    ASSIGN->Productions.push_back("N=f");//VAR=stringLiteral
    ASSIGN->Productions.push_back("N=N");//VAR=VAR
    ASSIGN->Productions.push_back("N=O");//VAR=NUMEXPR
    ASSIGN->Productions.push_back("N=R");//VAR=BOOL
    //add to list
    listNT.push_back(ASSIGN);

    //NUMEXPR
    shared_ptr<nonTerminal> NUMEXPR = make_shared<nonTerminal>();
    NUMEXPR->type = "O";
    NUMEXPR->Productions.push_back("N");//VAR
    NUMEXPR->Productions.push_back("g");//integerLiteral
    NUMEXPR->Productions.push_back("P");//CALC
    //add to list
    listNT.push_back(NUMEXPR);
    
    //CALC
    shared_ptr<nonTerminal> CALC = make_shared<nonTerminal>();
    CALC->type = "P";
    CALC->Productions.push_back("h(O,O)");//add(NUMEXPR,NUMEXPR)
    CALC->Productions.push_back("i(O,O)");//sub(NUMEXPR,NUMEXPR)
    CALC->Productions.push_back("j(O,O)");//mult(NUMEXPR,NUMEXPR)
    //add to list
    listNT.push_back(CALC);

    //BOOL
    shared_ptr<nonTerminal> BOOL = make_shared<nonTerminal>();
    BOOL->type = "R";
    BOOL->Productions.push_back("n(N,N)");//eq(VAR,VAR)
    BOOL->Productions.push_back("(N<N)");//(VAR<VAR)
    BOOL->Productions.push_back("(N>N)");//(VAR>VAR)
    BOOL->Productions.push_back("oR");//not BOOL
    BOOL->Productions.push_back("p(R,R)");//and(BOOL,BOOL)
    BOOL->Productions.push_back("q(R,R)");//or(BOOL,BOOL)
    BOOL->Productions.push_back("r");//T
    BOOL->Productions.push_back("s");//F
    BOOL->Productions.push_back("N");//VAR
    //add to list
    listNT.push_back(BOOL);

    //COND_BRANCH
    shared_ptr<nonTerminal> COND_BRANCH = make_shared<nonTerminal>();
    COND_BRANCH->type = "J";
    COND_BRANCH->Productions.push_back("k(R)l{D}");//if(BOOL)then{CODE}
    COND_BRANCH->Productions.push_back("k(R)l{D}m{D}");//if(BOOL)then{CODE}else{CODE}
    //add to list
    listNT.push_back(COND_BRANCH);

    //COND_LOOP
    shared_ptr<nonTerminal> COND_LOOP = make_shared<nonTerminal>();
    COND_LOOP->type = "S";
    COND_LOOP->Productions.push_back("t(R){D}");//while(BOOL){CODE}
    COND_LOOP->Productions.push_back("u(N=0;N<N;N=h(N,1)){D}");//for(VAR=0;VAR<VAR;VAR=add(VAR,1)){CODE}
    //add to list
    listNT.push_back(COND_LOOP);

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
//Q=>COND_BRANCH
//R=>BOOL
//S=>COND_LOOP
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
