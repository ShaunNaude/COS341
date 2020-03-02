#pragma once
#include <memory>
#include <list>
#include "lexer/token.hpp"

using namespace std;

class lexer {

public:
//=========================Variables============================
    list<shared_ptr <token> > tokenList;
//==============================================================

//=========================Functions============================
    lexer();
    ~lexer();
//==============================================================


};