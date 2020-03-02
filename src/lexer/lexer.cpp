#include "lexer/lexer.hpp"

lexer::lexer() {

}

lexer::~lexer() {

}
void lexer::start(string Input){

}
int lexer::isOperator(string Input, int start){

}
int lexer::isKeyword(string Input, int start){

}
int lexer::isString(string Input, int start){

}
int lexer::isVar(string Input, int start){

}
int lexer::isInt(string Input, int start){

} 
void lexer::AddNode(string Input, int start, int endS){

//============================================================
        //this function will add nodes to  Linked-list
//============================================================

        //Make the token we going to add.
        shared_ptr<token> T = make_shared<token> () ;

        //set variables
        T->token_str = Input;
        T->starting_Pos = start;
        T->ending_Pos = endS; 

        //add to linked list;
        this->tokenList.push_back(T);

        //exit function
        return;

}