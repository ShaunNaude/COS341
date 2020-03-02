#include "lexer/lexer.hpp"

lexer::lexer() {

}

lexer::~lexer() {

}
void lexer::start(string Input){
    int pos = 0;
    int checkPos = 0;
    bool Tokenized = false;
    //while not end of string
    while(Input.at(pos) != '\0'){  
        //while not end of line                                  
        while(Input.at(pos) != '#'){
            Tokenized = false;
            //operator                                
            if((Tokenized == false)&&()){
                checkPos = isOperator(Input, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }
            //keyword
            if((Tokenized == false)&&()){                               
                checkPos = isKeyword(Input, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }
            //string
            if((Tokenized == false)&&()){                               
                checkPos = isString(Input, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }
            //var(User defined)
            if((Tokenized == false)&&()){                               
                checkPos = isVar(Input, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }
            //int
            if((Tokenized == false)&&()){                               
                checkPos = isInt(Input, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }
            //none of them
            if(Tokenized == false){                               
                //error in input or our lexer
            }

        }
        //whatever our error resetting does.
        pos++;
    }
}
int lexer::isOperator(string Input, int start){
    return -1;
}
int lexer::isKeyword(string Input, int start){
    return -1;
}
int lexer::isString(string Input, int start){
    return -1;
}
int lexer::isVar(string Input, int start){
    return -1;
}
int lexer::isInt(string Input, int start){
    return -1;
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