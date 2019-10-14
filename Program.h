//
//  Program.hpp
//  z80asm
//
//  Created by Rafał Białek on 07/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include <string>
#include <sstream>
#include <list>

using namespace std;

#include "BinaryBlock.h"
#include "Exceptions.h"
#include "Instruction.h"
#include "DataBlock.h"
#include "SymbolTable.h"
#include "InstructionTable.h"

class Program {
    
    enum LineType {
        instruction,
        symbolDeclaration,
        dataDeclaration,
        emptyLine
    };
    
    list<BinaryBlock*>      machineCode;
    SymbolTable             symbolTable;
    InstructionTable        instructionTable;
    
    LineType getType(string line);
    string trimLine(string line);
    
    unsigned int readInstruction(string line);
    void readSymbol(string line, long address);
    unsigned int readData(string line);
    
    void resolveInstructions();
    
    void readSource(string source);
    
public:
    string getHex();
    string delcarationAtAddress(long address);
    
    Program(string source = "");
    ~Program();
};

#endif /* Program_hpp */
