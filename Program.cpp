//
//  Program.cpp
//  z80asm
//
//  Created by Rafał Białek on 07/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#include "Program.h"

Program::Program(string source) {
    readSource(source);
}

Program::~Program() {
    
}

Program::LineType Program::getType(string line) {
    if ( line.find(":") != string::npos )
        return symbolDeclaration;
    else if ( line.find(".") != string::npos )
        return dataDeclaration;
    else if ( line.length() == 0 )
        return emptyLine;
    else
        return instruction;
}

string Program::trimLine(string line) {
    string trimmed;
    if(line.length() == 0)
        return trimmed;
    
    string::const_iterator lineIter = line.cbegin();
    string::const_iterator lineEnd = line.cend();
    
    while(lineIter != lineEnd && isspace(*lineIter))
        lineIter++; //ommit whitespace
    
    while (lineIter != lineEnd && *lineIter != ';') {
        trimmed+=*(lineIter++); //read to the end or to the start of comment
    }

    while(isspace(trimmed[trimmed.length() - 1])) {
        trimmed.pop_back(); //remove spaces at the back
    }
    
    return trimmed;
}

unsigned int Program::readInstruction(string line) {
    Instruction *instruction = new Instruction(line, instructionTable);
    
    machineCode.push_back(instruction);
    return instruction->getLength();
}

unsigned int Program::readData(string line) {
    DataBlock *data = new DataBlock(line);
    
    machineCode.push_back(data);
    return data->getLength();
}

void Program::readSymbol(string line, long address) {
    string name;
    
    string::const_iterator line_iter = line.cbegin();
    string::const_iterator line_end = line.cend();
    
    while (line_iter != line_end && *line_iter != ':') {
        char current = *line_iter++;
        if(isspace(current))
            throw new MalformedSymbolDeclarationException(line);
        
        name += tolower(current);
    }
    
    symbolTable.declareSymbol(name, address);
}

void Program::resolveInstructions() {
    list<BinaryBlock*>::iterator iterator;
    for(iterator = machineCode.begin(); iterator != machineCode.end(); iterator++) {
        Instruction *instruction = dynamic_cast<Instruction*>(*iterator);
        if ( instruction != nullptr)
            instruction->resolve(symbolTable);
    }
}

string Program::getHex() {
    stringstream hexStream;

    list<BinaryBlock*>::iterator iterator;
    for(iterator = machineCode.begin(); iterator != machineCode.end(); iterator++) {
        Instruction *instruction = dynamic_cast<Instruction*>(*iterator);
        if ( instruction != nullptr ) {
            assert(instruction->isResolved());
        }
        hexStream<<(*iterator)->getHexString();
    }

    return hexStream.str();
}

void Program::readSource(string source) {
    if (source.length() == 0)
        return;
    
    istringstream sourceStream(source);
    string line;
    
    unsigned int lineCounter = 1;
    unsigned int currentAddress = 0;
    
    while (getline(sourceStream, line)) {
        //process line by line
        string trimmed = trimLine(line);
        LineType type = getType(trimmed);
        
        try {
            switch (type) {
                case symbolDeclaration:
                    readSymbol(trimmed, currentAddress);
                    break;

                case dataDeclaration:
                    currentAddress += readData(trimmed);
                    break;

                case instruction:
                    currentAddress += readInstruction(trimmed);
                    break;

                case emptyLine:
                default:
                    break;
            }
        } catch ( ProgramException *e ) {
            e->setLine(lineCounter);
            throw e;
        }
        
        lineCounter++;
    }
    
    resolveInstructions();
}

string Program::delcarationAtAddress(long address) {
    long counter=0;
    
    list<BinaryBlock*>::iterator iterator;
    for(iterator = machineCode.begin(); iterator != machineCode.end(); iterator++) {
        long start = counter, end = counter + (*iterator)->getLength();
        
        if ( address >= start && address < end )
            return (*iterator)->getDeclaration();
        
        counter = end;
    }
    
    return "";
}
