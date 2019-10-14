//
//  Instruction.cpp
//  z80asm
//
//  Created by Rafał Białek on 21/10/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#include "Instruction.h"

bool Instruction::isReserved(string expression) {
    static set<string> reserved_names = {       "a", "b", "c", "d", "e", "h", "l",
                                                "bc", "de", "hl", "ix", "iy",
                                                "f", "z", "nz", "c", "nc", "po", "pm", "p", "m",
                                                "sp", "pc",
                                                "i", "r"};
    
    return reserved_names.find(expression) != reserved_names.end();
}

Instruction::Instruction(string raw, InstructionTable& instructionTable)
:BinaryBlock(raw)
{
    parse(raw);
    binary = instructionTable.getBinary(normal);
}

void Instruction::resolve(SymbolTable &symbolTable) {
    list<long> resolved;
    
    for ( list<Immediate>::iterator i=immediates.begin(); i != immediates.end(); i++ ) {
        if(i->isResolved()) {
            resolved.push_back(i->getValue());
        }
        else {
            i->resolve(symbolTable);
            resolved.push_back(i->getValue());
        }
    }
    
    binary.resolve(resolved);
}

bool Instruction::isResolved() {
    for ( list<Immediate>::const_iterator i=immediates.cbegin(); i != immediates.cend(); i++ ) {
        if(!i->isResolved())
            return false;
    }
    if(!binary.isResolved())
        return false;
    return true;
}

unsigned int Instruction::getLength() {
    return binary.length();
}

string Instruction::getHexString() {
    if(!isResolved())
        return "";
    return binary.getResolved();
}

/*
 *  The normal form is defined as follows:
 *  Istruction is of format mnemonic[ openrand][,operand]
 *  mnemonic    :   lower case string consisting of letters only
 *  operand     :   register, or "%i" escape for anything that can vary
 *                  the whitespace before the first operand and a coma
 *                  before the second operand are required
 *
 *  The immediates can be expessed with base prefix ("0b", "0d", "0x")
 *  or without it (decimal will be asummed).
 */

void Instruction::parse(string raw) {
    string::const_iterator raw_iter = raw.cbegin();
    string::const_iterator raw_end = raw.cend();
    
    string mnemonic;
    
    StringUtilities::ommitSpaces(raw_iter, raw_end);
    
    while(raw_iter != raw_end && !isspace(*raw_iter)) {
        if (isalpha(*raw_iter))
            normal += tolower(*raw_iter);
        else {
            //illegar characters in mnemonic
            throw new InvalidCharacterInMnemonicException(*raw_iter);
        }
        raw_iter++;
    }
    
    mnemonic = normal;
    bool substituteImmediate = true;
    
    if ( mnemonic == "rst" || mnemonic == "bit" || mnemonic == "res" || mnemonic == "set" ) {
        substituteImmediate = false;   //special case of instructions that specify a number
    }
    
    StringUtilities::ommitSpaces(raw_iter, raw_end);
    
    if ( raw_iter == raw_end ) {
        //at the end of string, this was only the mnemonic and no operands
        return;
    }
    normal += ' ';      //add the space between mnemonic and operand
    
    //the rest of the instruction can be rewritten in lowercase ommitin every whitespace
    //if any immadiate is encountered it is converted to escape and put on the immediate list
    
    while ( raw_iter != raw_end ) {
        if ( isdigit(*raw_iter) ) {
            //immediate here
            string digits;
            long value = StringUtilities::readNumber(raw_iter, raw_end, &digits);
            
            if ( raw_iter != raw_end && !isspace(*raw_iter) && *raw_iter != ')' ) {
                //error reading
                throw new InvalidCharactersInValueException(*raw_iter);
            }
            
            if ( !substituteImmediate ) {
                //flag for those special instructions
                substituteImmediate = true;
                normal += digits;
            }
            else {
                normal.append("%i");
                //add to immediate list
                Immediate immediate(value);
                immediates.push_back(immediate);
            }
            
            if ( raw_iter == raw_end )
                break;  //nothing to see here anymore
        }
        
        if ( isalpha(*raw_iter) ) {
            //symbol or register
            
            string expression;
            while ( raw_iter != raw_end && isalpha(*raw_iter) ) {
                expression += tolower(*(raw_iter++));
            }
            
            if ( isReserved(expression) ) {
                normal.append(expression);
            }
            else {
                normal.append("%i");
                //add to immediate list
                Immediate immediate(expression);
                immediates.push_back(immediate);
            }
            
            if ( raw_iter == raw_end )
                break;  //nothing to see here anymore
        }
        
        
        if ( !isspace(*raw_iter) ) {
            normal += tolower(*raw_iter);
        }
        raw_iter++;
    }
}

