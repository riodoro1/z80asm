//
//  Immediate.hpp
//  z80asm
//
//  Created by Rafał Białek on 28/10/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef Immediate_hpp
#define Immediate_hpp

#include <stdio.h>

#include <string>

#include "SymbolTable.h"

using namespace std;

struct Immediate {
private:
    long value;
    string symbol;
    bool _isResolved;
    
public:
    
    Immediate(string symbol)
    :symbol(symbol)
    ,_isResolved(false)
    {
        
    }
    
    Immediate(long value)
    :value(value)
    ,_isResolved(true)
    {
        
    }
    
    void resolve(SymbolTable &symbols) {
        if(_isResolved)
            return;
        value = symbols.getValue(symbol);
        _isResolved = true;
    }
    
    bool isResolved() const {
        return _isResolved;
    }
    
    long getValue() const {
        return value;
    }
    
    string getSymbol() const {
        return symbol;
    }
    
};

#endif /* Immediate_hpp */
