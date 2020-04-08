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

    
    
    





}

















































///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void parser::addGrammar(){

    //PROG
    shared_ptr<nonTerminal> PROG = make_shared<nonTerminal>();
    PROG->type = "PROG";
    PROG->Productions.push_back("CODE");
    PROG->Productions.push_back("CODE;PROC_DEFS");
    //add to list
    listNT.push_back(PROG);


    //CODE
    shared_ptr<nonTerminal> CODE = make_shared<nonTerminal>();
    CODE->type = "CODE";
    CODE->Productions.push_back("INSR");
    CODE->Productions.push_back("INSTR;CODE");
    //add to list
    listNT.push_back(CODE);

    //PROC_DEFS
    shared_ptr<nonTerminal> PROC_DEFS = make_shared<nonTerminal>();
    PROC_DEFS->type = "PROC_DEFS";
    PROC_DEFS->Productions.push_back("PROC");
    PROC_DEFS->Productions.push_back("PROC&PROC_DEFS");
    //add to list
    listNT.push_back(PROC_DEFS);

    //PROC
    shared_ptr<nonTerminal> PROC = make_shared<nonTerminal>();
    PROC->type = "PROC";
    PROC->Productions.push_back("proc userDefinedIdentifier{PROG}");
    //add to list
    listNT.push_back(PROC);

    //INSTR
    shared_ptr<nonTerminal> INSTR = make_shared<nonTerminal>();
    INSTR->type = "INSTR";
    INSTR->Productions.push_back("halt");
    INSTR->Productions.push_back("DECL");
    INSTR->Productions.push_back("IO");
    INSTR->Productions.push_back("CALL");
    INSTR->Productions.push_back("ASSIGN");
    INSTR->Productions.push_back("COND_BRANCH");
    INSTR->Productions.push_back("COND_LOOP");
    //add to list
    listNT.push_back(INSTR);


    //IO
    shared_ptr<nonTerminal> IO = make_shared<nonTerminal>();
    IO->type = "IO";
    IO->Productions.push_back("input(VAR)");
    IO->Productions.push_back("output(VAR)");
    //add to list
    listNT.push_back(IO);

    //CALL
    shared_ptr<nonTerminal> CALL = make_shared<nonTerminal>();
    CALL->type = "CALL";
    CALL->Productions.push_back("userDefinedIdentifier");
    //add to list
    listNT.push_back(CALL);

    //DECL 
    shared_ptr<nonTerminal> DECL = make_shared<nonTerminal>();
    DECL->type = "DECL";
    DECL->Productions.push_back("TYPE&NAME");
    DECL->Productions.push_back("TYPE&NAME;DECL");
    //add to list
    listNT.push_back(DECL);

    //TYPE 
    shared_ptr<nonTerminal> TYPE = make_shared<nonTerminal>();
    TYPE->type = "TYPE";
    TYPE->Productions.push_back("num");
    TYPE->Productions.push_back("string");
    TYPE->Productions.push_back("bool");
    //add to list
    listNT.push_back(TYPE);

    //NAME
    shared_ptr<nonTerminal> NAME = make_shared<nonTerminal>();
    NAME->type = "NAME";
    NAME->Productions.push_back("userDefinedIdentifier");
    //add to list
    listNT.push_back(NAME);

    //VAR
    shared_ptr<nonTerminal> VAR = make_shared<nonTerminal>();
    VAR->type = "VAR";
    VAR->Productions.push_back("userDefinedIdentifier");
    //add to list
    listNT.push_back(VAR);

    //ASSIGN
    shared_ptr<nonTerminal> ASSIGN = make_shared<nonTerminal>();
    ASSIGN->type = "ASSIGN";
    ASSIGN->Productions.push_back("VAR=stringLiteral");
    ASSIGN->Productions.push_back("VAR=VAR");
    ASSIGN->Productions.push_back("VAR=NUMEXPR");
    ASSIGN->Productions.push_back("VAR=BOOL");
    //add to list
    listNT.push_back(ASSIGN);

    //NUMEXPR
    shared_ptr<nonTerminal> NUMEXPR = make_shared<nonTerminal>();
    NUMEXPR->type = "NUMEXPR";
    NUMEXPR->Productions.push_back("VAR");
    NUMEXPR->Productions.push_back("integerLiteral");
    NUMEXPR->Productions.push_back("CALC");
    //add to list
    listNT.push_back(NUMEXPR);
    
    //CALC
    shared_ptr<nonTerminal> CALC = make_shared<nonTerminal>();
    CALC->type = "CALC";
    CALC->Productions.push_back("add(NUMEXPR,NUMEXPR)");
    CALC->Productions.push_back("sub(NUMEXPR,NUMEXPR)");
    CALC->Productions.push_back("mult(NUMEXPR,NUMEXPR)");
    //add to list
    listNT.push_back(CALC);

    //COND_BRANCH
     shared_ptr<nonTerminal> COND_BRANCH = make_shared<nonTerminal>();
    COND_BRANCH->type = "COND_BRANCH";
    COND_BRANCH->Productions.push_back("if(BOOL)then{CODE}");
    COND_BRANCH->Productions.push_back("if(BOOL)then{CODE}else{CODE}");
    //add to list
    listNT.push_back(COND_BRANCH);

    //BOOL
    shared_ptr<nonTerminal> BOOL = make_shared<nonTerminal>();
    BOOL->type = "BOOL";
    BOOL->Productions.push_back("eq(VAR,VAR)");
    BOOL->Productions.push_back("(VAR<VAR)");
    BOOL->Productions.push_back("(VAR>VAR)");
    BOOL->Productions.push_back("not BOOL");
    BOOL->Productions.push_back("and(BOOL,BOOL)");
    BOOL->Productions.push_back("or(BOOL,BOOL)");
    BOOL->Productions.push_back("T");
    BOOL->Productions.push_back("F");
    BOOL->Productions.push_back("VAR");
    //add to list
    listNT.push_back(BOOL);

    //COND_BRANCH
     shared_ptr<nonTerminal> COND_BRANCH = make_shared<nonTerminal>();
    COND_BRANCH->type = "COND_BRANCH";
    COND_BRANCH->Productions.push_back("if(BOOL)then{CODE}");
    COND_BRANCH->Productions.push_back("if(BOOL)then{CODE}else{CODE}");
    //add to list
    listNT.push_back(COND_BRANCH);

    //COND_LOOP
    shared_ptr<nonTerminal> COND_LOOP = make_shared<nonTerminal>();
    COND_LOOP->type = "COND_LOOP";
    COND_LOOP->Productions.push_back("while(BOOL){CODE}");
    COND_LOOP->Productions.push_back("for(VAR=0;VAR<VAR;VAR=add(VAR,1)){CODE}");
    //add to list
    listNT.push_back(COND_LOOP);



    return
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////