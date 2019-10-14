//
//  EscapedBinary.hpp
//  z80asm
//
//  Created by Rafał Białek on 24/10/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef EscapedBinary_hpp
#define EscapedBinary_hpp

#include <assert.h>

#include <string>
#include <list>

#include "Exceptions.h"

using namespace std;

class EscapedBinary {
private:
    string hexWithEscape;
    string *resolved;
    
    static char charToNum(char);
    
public:
    EscapedBinary();
    EscapedBinary(string string);
    
    unsigned int length();
    void resolve(list<long> immediates);
    bool isResolved();
    string getResolved();
    
    ~EscapedBinary();
};

#endif /* EscapedBinary_hpp */
