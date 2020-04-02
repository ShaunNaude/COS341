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
                pos++;                      
                continue;
            }

            if( (Tokenized == false) ){                               
                char error=result[pos];
                string s = "LexicalError[line:" + to_string(currentLine)+ ",col:" + to_string(pos)+ "]: '" + error + "' is Not a valid character";
                logError(s);
                pos++;
            }

        }
        //whatever our error resetting does.
        pos++;
        //this keeps track of what line we are currently reading *used for errorLog*
        currentLine++;
        //this keeps track of what column we are currently reading *used for errorLog*
        currentCol=1;
    }

    cout<<"here"<<endl;
}

int lexer::isOperator(string Input, int start){
    string ValOperators = "<>(){}=,;";
    int end = start;
    if(((int)ValOperators.find(Input.at(start)) >= 0)){
        if(Input.at(start)=='<'){
            AddNode("lthan", start, end, "<");
        }else if(Input.at(start)=='>'){
            AddNode("gthan", start, end, ">");
        }else if(Input.at(start)=='('){
            AddNode("oparen", start, end, "(");
        }else if(Input.at(start)==')'){
            AddNode("cparen", start, end, ")");
        }else if(Input.at(start)=='{'){
            AddNode("obrace", start, end, "{");
        }else if(Input.at(start)=='}'){
            AddNode("cbrace", start, end, "}");
        }else if(Input.at(start)=='='){
            AddNode("equal", start, end, "=");
        }else if(Input.at(start)==','){
            AddNode("comma", start, end, ",");
        }else if(Input.at(start)==';'){
            AddNode("semicolon", start, end, ";");
        }
        currentCol++;
        return (end+1);
    }else
        return -1;
}

/*
======================================================================================================================================
                                            IsKeyword Function start               
======================================================================================================================================
*/
int lexer::isKeyword(string Input, int start){
    int end = start;
    if(Input.at(end) == 'i'){
        if(Input.at(end+1) == 'f'){
            end = end + 1;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            //add to all
            AddNode("if", start, end, "if");
            return end+1;
        }
        if((Input.at(end+1)== 'n')&&(Input.at(end+2)== 'p')&&(Input.at(end+3)== 'u')&&(Input.at(end+4)== 't')){
            end = end + 4;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            //add to all
            AddNode("input", start, end, "input");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'b'){
        if ((Input.at(end+1)== 'o')&&(Input.at(end+2)== 'o')&&(Input.at(end+3)== 'l')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("bool", start, end, "bool");
            return end+1;
        }else{
            return -1;
        }
        
    }else if(Input.at(end) == 'w'){
        if ((Input.at(end+1)== 'h')&&(Input.at(end+2)== 'i')&&(Input.at(end+3)== 'l')&&(Input.at(end+4)== 'e')){
            end = end + 4;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("while", start, end, "while");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'e'){
        if ((Input.at(end+1)== 'l')&&(Input.at(end+2)== 's')&&(Input.at(end+3)== 'e')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("else", start, end, "else");
            return end+1;
        }
        if((Input.at(end+1)== 'q')){
            end = end + 1;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("eq", start, end, "eq");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 't'){
        if ((Input.at(end+1)== 'h')&&(Input.at(end+2)== 'e')&&(Input.at(end+3)== 'n')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("then", start, end, "then");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'a'){
        if ((Input.at(end+1)== 'n')&&(Input.at(end+2)== 'd')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("and", start, end, "and");
            return end+1;
        }
        if ((Input.at(end+1)== 'd')&&(Input.at(end+2)== 'd')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("add", start, end, "add");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'n'){
        if ((Input.at(end+1)== 'u')&&(Input.at(end+2)== 'm')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("num", start, end, "num");
            return end+1;
        }
        if ((Input.at(end+1)== 'o')&&(Input.at(end+2)== 't')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("not", start, end, "not");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'o'){
        if ((Input.at(end+1)== 'r')){
            end = end + 1;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("or", start, end, "or");
            return end+1;
        }
        if ((Input.at(end+1)== 'u')&&(Input.at(end+2)== 't')&&(Input.at(end+3)== 'p')&&(Input.at(end+4)== 'u')&&(Input.at(end+5)== 't')){
            end = end + 5;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("output", start, end, "output");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'T'){
        if(!OperatorNext(Input.at(end+2))){return -1;};
        AddNode("T", start, end, "T");
        return end+1;
    }else if(Input.at(end) == 'F'){
        if(!OperatorNext(Input.at(end+2))){return -1;};
        AddNode("F", start, end, "F");
        return end+1;
    }else if(Input.at(end) == 's'){
        if ((Input.at(end+1)== 'u')&&(Input.at(end+2)== 'b')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("sub", start, end, "sub");
            return end+1;
        }
        if ((Input.at(end+1)== 't')&&(Input.at(end+2)== 'r')&&(Input.at(end+3)== 'i')&&(Input.at(end+4)== 'n')&&(Input.at(end+5)== 'g')){
            end = end + 5;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("string", start, end, "string");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'f'){
        if ((Input.at(end+1)== 'o')&&(Input.at(end+2)== 'r')){
            end = end + 2;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("for", start, end, "for");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'm'){
        if ((Input.at(end+1)== 'u')&&(Input.at(end+2)== 'l')&&(Input.at(end+3)== 't')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("mult", start, end, "mult");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'h'){
        if ((Input.at(end+1)== 'a')&&(Input.at(end+2)== 'l')&&(Input.at(end+3)== 't')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("halt", start, end, "halt");
            return end+1;
        }else{
            return -1;
        }
    }else if(Input.at(end) == 'p'){
        if ((Input.at(end+1)== 'r')&&(Input.at(end+2)== 'o')&&(Input.at(end+3)== 'c')){
            end = end + 3;
            if(!OperatorNext(Input.at(end+1))){return -1;};
            AddNode("proc", start, end, "proc");
            return end+1;
        }else{
            return -1;
        }
    }else{
        return -1;
    }
}

/*
======================================================================================================================================
                                            IsKeyword Function END               
======================================================================================================================================
*/


/*
======================================================================================================================================
                                            IsString Function START               
======================================================================================================================================
*/
int lexer::isString(string Input, int start){

    //////////////////////////////////////////////////////
        //THIS FUNCTION IS BEING DONE BY SHAUN
    /////////////////////////////////////////////////////

    //input is the current line
    //start should be a  ' " ' 
    //i need to identify a string that is 8 character long, not including quotes
    //the string is defined by this REGEX = [a-z0-9space]{0-8}
    //we only return -1 if it could not be tokenized
    //if we hit a lex error write the error str to the txt file and continue from the end of the error str

    /*
    -> easiest way to check if the str has an end quote
        -> copy from pos=1 until the end of the input *(therefor we are cutting out the open quote that got us here)
        -> first check if there is a ' " ' i
            -> if there is a quote somehere in the string, read up until that quote
            -> be sure to check the length as u go along so u can record errors.
            ->in this statement is where possible tokenization can happen
            -> if we have an error eg too long OR invalid char, be sure to send the position where the str ended so we can ignore that piece
                and tokenize the rest of the file.

        -> lets say there is not an end quote in the line, now we already know the str is invalid... 
        -> we need to read up until the point where the quote should have been and record that as our error.
        -> be sure to send back the position that is after the faulty string so we can continue parsing our file.
            */

    /*
    

    */
        list<int> errors;
        bool invalidChar = false;
        bool lengthError = false;
        string errorLine="";
        //this copies the entire line except for the starting open quote
       
        string line= Input.substr(start+1,Input.length());
        
        

            //if this is true we have a closing quote
        if( (int)line.find('"') >= 0)
        {
            //read while pos!=' " '
            //{
                //if the length is greater than 8 
                    //send error message to error logger
                        //BE SURE TO CHECK IF A INVAILID CHARACTER WAS HIT 

                //if invalid character make bool true, record position of error in vector

            //}

            int pos=0;

            while(line[pos] != '"')
            {
                if( isValid(line[pos]) == false )
                {
                    invalidChar = true;
                    exit;
                }

                if(pos>8)
                {
                    lengthError = true;
                    exit;
                }
                pos++;
            }

            if(lengthError==false && invalidChar==false)
            {
                //tokenize //type ,start,end,actual
                AddNode("String",start,start+pos+1,line.substr(0,pos));
                return start+pos+2;
                
            }

            else{
                    if (lengthError == true)
                    {
                        errorLine = '"'+line.substr(0,9);
                       errorLine = "LexicalError[line:" + to_string(currentLine)+ ",col:" + to_string(start) + "-" + to_string(start+9)  + "]: '"+ errorLine + "' strings have at most 8 characters"; 
                       logError(errorLine);
                       
                    }

                    if(invalidChar == true)
                    {
                        
                        if(lengthError==false)
                        {
                            errorLine = line.substr(0,pos);
                            errorLine = "LexicalError[line:" + to_string(currentLine)+ ",col:" + to_string(start) + "-" + to_string(start+pos+1)  + "]: '" + '"' + errorLine + '"' + "' string contains invalid characters";
                        }
                        else{
                            errorLine = line.substr(0,9);
                            errorLine = "LexicalError[line:" + to_string(currentLine)+ ",col:" + to_string(start) + "-" + to_string(start+9)  + "]: '" + '"' + errorLine + '"' + "' string contains invalid characters";
                        }
                        logError(errorLine);

                    }

                    
                        return start+pos+2;
                    
                    
            }

        }
        
        else{
            //if we are here it means there is no closing quote

                //make a function to log errors
                    //we will possibly have 2 errors here definatly str too long and we must check if there are invalid characters in the designated 8 chars
                    //the error logger function needs to be sent the error message, all the error logger must do is write to txtfile
            
            errorLine = '"'+line.substr(0,9);

            errorLine =  "LexicalError[line:" + to_string(currentLine)+ ",col:" + to_string(start) + "-" + to_string(start+9)  + "]: '"+ errorLine +"' strings have at most 8 characters";

            logError(errorLine);
            errorLine="";

            for(int i = 0 ; i<line.length() ; i++)
                {
                    if( isValid(line[i]) == false )
                    {
                        invalidChar = true;
                        exit;
                    }
                }

                    if(invalidChar == true)
                    {
                        errorLine = "LexicalError[line:" + to_string(currentLine)+ ",col:" + to_string(start) + "-" + to_string(start+9)  + "]: '" + '"' + errorLine + '"' + "' string contains invalid characters";
                        logError(errorLine);
                    }
                 

             
             return start+10;
        }












    
}
/*
======================================================================================================================================
                                            IsString Function END              
======================================================================================================================================
*/


int lexer::isVar(string Input, int start){
    string VarStart = "abcdefghijklmnopqrstuvwxyz";
    string VarChars = "abcdefghijklmnopqrstuvwxyz0123456789";
    string Word = "";
    int end = start;
    if(((int)VarStart.find(Input.at(start)) >= 0)){
        while((int)VarChars.find(Input.at(end)) >= 0){
            Word += Input.at(end);
            end++;
        }
        AddNode("var", start, end-1, Word);
        return (end);
    }else{
        return -1;
    }
}
int lexer::isInt(string Input, int start){
    string IntVals = "123456789";
    string MyInt = "";
    int end = start;
    if(((int)IntVals.find(Input.at(start)) >= 0)||(Input.at(start)=='-')){
        IntVals += "0";
        while((int)IntVals.find(Input.at(end)) >= 0){
            MyInt += Input.at(end);
            end++;
        }
        AddNode("int", start, end-1, MyInt);
        return (end);
    }else if(Input.at(start)=='0'){
        IntVals += "0";
        while(((int)IntVals.find(Input.at(start)) >= 0)){
            MyInt += Input.at(end);
            end++;
        }
        logError("Lexical Error [line: "+to_string(currentLine)+", col: "+to_string(currentCol)+"]: "+to_string(MyInt)+" can't start with 0");
        currentCol=currentCol+start-end;
        return end;
    }else
        return -1;
} 
void lexer::AddNode(string type, int start, int endS, string InputStr){

//============================================================
        //this function will add nodes to  Linked-list
//============================================================

        //Make the token we going to add.
        shared_ptr<token> T = make_shared<token> () ;

        //set variables
        T->token_type = type;
        T->token_str = InputStr;
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

bool lexer::isValid(char MyChar){
//============================================================
    //this function will true if mychar = REGEX = [a-z0-9space]{0-8}
//============================================================

    string valid = "abcdefghijklmnopqrstuvwxyz0123456789 ";

    if(( (int)valid.find(MyChar) >= 0 ))
        return true;
    else return false;
    

}

void lexer::logError(string error){
//=========================================================================
                //this will cout the error
//=========================================================================
    cout<<error<<endl;
    

}