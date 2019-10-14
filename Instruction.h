//
//  Instruction.hpp
//  z80asm
//
//  Created by Rafał Białek on 21/10/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef Instruction_hpp
#define Instruction_hpp

#include <string>
#include <list>
#include <set>
#include <iostream>

#include "BinaryBlock.h"
#include "Exceptions.h"
#include "Immediate.h"
#include "EscapedBinary.h"
#include "InstructionTable.h"
#include "StringUtilities.h"

using namespace std;

class Instruction : public BinaryBlock {
private:
    
    string          normal;                 //instruction in normal form
    list<Immediate> immediates;             //list of immediates as they appear in instruction
    EscapedBinary   binary;                 //binary to be filled with immediate values
    
    static bool isReserved(string);         //reserved names checking
    void parse(string raw);                 //normalizing instruction format
    
public:
    
    Instruction(string, InstructionTable&);
    void resolve(SymbolTable&);
    
    bool isResolved();
    
    unsigned int getLength();
    string getHexString();
};


#endif /* Instruction_hpp */
