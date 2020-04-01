#pragma once

#include <string>
#include <iostream>

using namespace std;

class token {

public:
    token(){};
    ~token(){};

    string token_str;
    string token_type;
    int starting_Pos;
    int ending_Pos;


};