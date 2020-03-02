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
    int end = start;
    if(start!=0){
        if ((Input.at(start-1)!='#')||(Input.at(start-1)!=' ')){
            return -1;
        }
        
    }
    if(Input.at(end) == 'i'){
        if(Input.at(end+1) == 'f'){
            end = end + 1;
            //add to all
            if ((Input.at(end+1) != '(')||(Input.at(end+1) != ' '))
            {
                return -1;
            }
            //
            AddNode(Input, start, end);
            return end+1;
        }
        if((Input.at(end+1) = 'n')&&(Input.at(end+2) = 'p')&&(Input.at(end+3) = 'u')&&(Input.at(end+4) = 't')){
            end = end + 4;
            //add to all
            if ((Input.at(end+1) != '(')||(Input.at(end+1) != ' '))
            {
                return -1;
            }
            //
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'b'){
        if ((Input.at(end+1) = 'o')&&(Input.at(end+2) = 'o')&&(Input.at(end+3) = 'l')){
            end = end + 3;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
        
    }else if(Input.at(end) == 'w'){
        if ((Input.at(end+1) = 'h')&&(Input.at(end+2) = 'i')&&(Input.at(end+3) = 'l')&&(Input.at(end+4) = 'e')){
            end = end + 4;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'e'){
        if ((Input.at(end+1) = 'l')&&(Input.at(end+2) = 's')&&(Input.at(end+3) = 'e')){
            end = end + 3;
            AddNode(Input, start, end);
            return end+1;
        }if((Input.at(end+1) = 'q')){
            end = end + 1;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 't'){
        if ((Input.at(end+1) = 'h')&&(Input.at(end+2) = 'e')&&(Input.at(end+3) = 'n')){
            end = end + 3;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'a'){
        if ((Input.at(end+1) = 'n')&&(Input.at(end+2) = 'd')){
            end = end + 2;
            AddNode(Input, start, end);
            return end+1;
        }
        if ((Input.at(end+1) = 'd')&&(Input.at(end+2) = 'd')){
            end = end + 2;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'n'){
        if ((Input.at(end+1) = 'u')&&(Input.at(end+2) = 'm')){
            end = end + 2;
            AddNode(Input, start, end);
            return end+1;
        }
        if ((Input.at(end+1) = 'o')&&(Input.at(end+2) = 't')){
            end = end + 2;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'o'){
        if ((Input.at(end+1) = 'r')){
            end = end + 1;
            AddNode(Input, start, end);
            return end+1;
        }
        if ((Input.at(end+1) = 'u')&&(Input.at(end+2) = 't')&&(Input.at(end+3) = 'p')&&(Input.at(end+4) = 'u')&&(Input.at(end+5) = 't')){
            end = end + 5;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'T'){
        AddNode(Input, start, end);
        return end+1;
    }else if(Input.at(end) == 'F'){
        AddNode(Input, start, end);
        return end+1;
    }else if(Input.at(end) == 's'){
        if ((Input.at(end+1) = 'u')&&(Input.at(end+2) = 'b')){
            end = end + 2;
            AddNode(Input, start, end);
            return end+1;
        }
        if ((Input.at(end+1) = 't')&&(Input.at(end+2) = 'r')&&(Input.at(end+3) = 'i')&&(Input.at(end+4) = 'n')&&(Input.at(end+5) = 'g')){
            end = end + 5;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'f'){
        if ((Input.at(end+1) = 'o')&&(Input.at(end+2) = 'r')){
            end = end + 2;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'm'){
        if ((Input.at(end+1) = 'u')&&(Input.at(end+2) = 'l')&&(Input.at(end+3) = 't')){
            end = end + 3;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'h'){
        if ((Input.at(end+1) = 'a')&&(Input.at(end+2) = 'l')&&(Input.at(end+3) = 't')){
            end = end + 3;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'p'){
        if ((Input.at(end+1) = 'r')&&(Input.at(end+2) = 'o')&&(Input.at(end+3) = 'c')){
            end = end + 3;
            AddNode(Input, start, end);
            return end+1;
        }else{
            return -1;
        }
    }else{
        return -1;
    }
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

}