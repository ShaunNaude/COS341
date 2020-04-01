#include "lexer/lexer.hpp"

lexer::lexer() {

}

lexer::~lexer() {

}
void lexer::start(string Input){
    //varibles 
    int pos = 0;
    int checkPos = 0;
    bool Tokenized = false;
    ifstream inputFile;
    string line,result;

    //these are all the possible operator tokens
    string operators = "<>(){}=,;";
    //these are all the Starting
    string keyLetters = "a,i,w,n,p,o,s,t,f,b,T,m,e,h,F";
    
    


    //open textfile
    inputFile.open("input.txt");

    //check if file is open
    if( inputFile.is_open() )
    {   
        //while loop that builds long string
        while( getline(inputFile,line) )
        {
            result = result+line;
        }
    }


    //while not end of string
    while(result.at(pos) != '\0'){  
        //while not end of line                                  
        while(result.at(pos) != '#'){
            Tokenized = false;

            //operator                  //this checks if pos is a operator              
            if((Tokenized == false)&&( (int)operators.find(result[pos]) >= 0 )){
                checkPos = isOperator(result, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }

            //keyword                   //this checks if  pos is keyLetter
            if((Tokenized == false)&&( (int)keyLetters.find( result.at(pos) ) >= 0 )){                               
                checkPos = isKeyword(result, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }
            //string                    //checks if its is open quote
            if((Tokenized == false)&&( result.at(pos) == '"' )){                               
                checkPos = isString(result, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }
            //var(User defined)         //compares ascii values ie a-z
            if((Tokenized == false)&&( result[pos] >= 'a' && result[pos] <= 'z' )){                               
                checkPos = isVar(result, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }
            //int                       //compares ascii values 0-9
            if((Tokenized == false)&&( result[pos] >= '0' && result[pos] <= '9')){                               
                checkPos = isInt(result, pos);
                if (checkPos != -1){//if no error found
                    pos = checkPos;
                    continue;
                }
            }
            //space
            if( (Tokenized == false)&&( result.at(pos) == ' ' )){                               
                continue;
            }

            if( (Tokenized == false) ){                               
                //add error message here
            }

        }
        //whatever our error resetting does.
        pos++;
    }
}

int lexer::isOperator(string Input, int start){
    string ValOperators = "<>(){}=,;";
    int end = start;
    if(((int)ValOperators.find(Input.at(start)) >= 0)){
        if(Input.at(start)=='<'){
            AddNode("lthan", start, end);
        }else if(Input.at(start)=='>'){
            AddNode("gthan", start, end);
        }else if(Input.at(start)=='('){
            AddNode("oparen", start, end);
        }else if(Input.at(start)==')'){
            AddNode("cparen", start, end);
        }else if(Input.at(start)=='{'){
            AddNode("obrace", start, end);
        }else if(Input.at(start)=='}'){
            AddNode("cbrace", start, end);
        }else if(Input.at(start)=='='){
            AddNode("equal", start, end);
        }else if(Input.at(start)==','){
            AddNode("comma", start, end);
        }else if(Input.at(start)==';'){
            AddNode("semicolon", start, end);
        }
        
        return (end+1);
    }else
        return -1;
}
int lexer::isKeyword(string Input, int start){
    int end = start;
    //check if end of line or a space then return and carry on.
    if(start!=0){
        if ((Input.at(start-1)!='#')||(Input.at(start-1)!=' ')){
            return -1;
        }
    }
    if(Input.at(end) == 'i'){
        if(Input.at(end+1) == 'f'){
            end = end + 1;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            //add to all
            AddNode("if", start, end);
            return end+1;
        }
        if((Input.at(end+1)== 'n')&&(Input.at(end+2)== 'p')&&(Input.at(end+3)== 'u')&&(Input.at(end+4)== 't')){
            end = end + 4;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            //add to all
            AddNode("input", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'b'){
        if ((Input.at(end+1)== 'o')&&(Input.at(end+2)== 'o')&&(Input.at(end+3)== 'l')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("bool", start, end);
            return end+1;
        }else{
            return -1;
        }
        
    }else if(Input.at(end) == 'w'){
        if ((Input.at(end+1)== 'h')&&(Input.at(end+2)== 'i')&&(Input.at(end+3)== 'l')&&(Input.at(end+4)== 'e')){
            end = end + 4;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("while", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'e'){
        if ((Input.at(end+1)== 'l')&&(Input.at(end+2)== 's')&&(Input.at(end+3)== 'e')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("else", start, end);
            return end+1;
        }
        if((Input.at(end+1)== 'q')){
            end = end + 1;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("eq", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 't'){
        if ((Input.at(end+1)== 'h')&&(Input.at(end+2)== 'e')&&(Input.at(end+3)== 'n')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("then", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'a'){
        if ((Input.at(end+1)== 'n')&&(Input.at(end+2)== 'd')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("and", start, end);
            return end+1;
        }
        if ((Input.at(end+1)== 'd')&&(Input.at(end+2)== 'd')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("add", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'n'){
        if ((Input.at(end+1)== 'u')&&(Input.at(end+2)== 'm')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("num", start, end);
            return end+1;
        }
        if ((Input.at(end+1)== 'o')&&(Input.at(end+2)== 't')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("not", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'o'){
        if ((Input.at(end+1)== 'r')){
            end = end + 1;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("or", start, end);
            return end+1;
        }
        if ((Input.at(end+1)== 'u')&&(Input.at(end+2)== 't')&&(Input.at(end+3)== 'p')&&(Input.at(end+4)== 'u')&&(Input.at(end+5)== 't')){
            end = end + 5;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("output", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'T'){
        if(!OperatorNext(Input.at(end+2))){return -1;};
        AddNode("T", start, end);
        return end+1;
    }else if(Input.at(end) == 'F'){
        if(!OperatorNext(Input.at(end+2))){return -1;};
        AddNode("F", start, end);
        return end+1;
    }else if(Input.at(end) == 's'){
        if ((Input.at(end+1)== 'u')&&(Input.at(end+2)== 'b')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("sub", start, end);
            return end+1;
        }
        if ((Input.at(end+1)== 't')&&(Input.at(end+2)== 'r')&&(Input.at(end+3)== 'i')&&(Input.at(end+4)== 'n')&&(Input.at(end+5)== 'g')){
            end = end + 5;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("string", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'f'){
        if ((Input.at(end+1)== 'o')&&(Input.at(end+2)== 'r')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("for", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'm'){
        if ((Input.at(end+1)== 'u')&&(Input.at(end+2)== 'l')&&(Input.at(end+3)== 't')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("mult", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'h'){
        if ((Input.at(end+1)== 'a')&&(Input.at(end+2)== 'l')&&(Input.at(end+3)== 't')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("halt", start, end);
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'p'){
        if ((Input.at(end+1)== 'r')&&(Input.at(end+2)== 'o')&&(Input.at(end+3)== 'c')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("proc", start, end);
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
    string VarStart = "abcdefghijklmnopqrstuvwxyz";
    string VarChars = "abcdefghijklmnopqrstuvwxyz0123456789";
    int end = start;
    if(((int)VarStart.find(Input.at(start)) >= 0)){
        while((int)VarChars.find(Input.at(end)) >= 0){
            end++;
        }
        AddNode("var", start, end-1);
        return (end);
    }else{
        return -1;
    }
}
int lexer::isInt(string Input, int start){
    string IntVals = "123456789";
    int end = start+1;
    if(((int)IntVals.find(Input.at(start)) >= 0)||(Input.at(start)=='-')){
        IntVals += "0";
        while((int)IntVals.find(Input.at(end)) >= 0){
            end++;
        }
        AddNode("int", start, end-1);
        return (end);
    }else
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
bool lexer::OperatorNext(char MyChar){
//============================================================
    //this function will return true if an operator or space comes next
//============================================================
    string ValOperators = "<>(){}=,; ";
    if(!((int)ValOperators.find(MyChar) >= 0)){
        return false;
    }
    return true;
}