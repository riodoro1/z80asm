//
//  InstructionExceptions.h
//  z80asm
//
//  Created by Rafał Białek on 03/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef InstructionExceptions_h
#define InstructionExceptions_h

#include "ProgramException.h"

class InstructionNotRecognizedException : public ProgramException {
    
    static string create_message(string normal) {
        stringstream message;
        message<<"Instruction with form: "<<normal<<" was not recognized.";
        return message.str();
    }
    
public:
    
    InstructionNotRecognizedException(string normal)
    :ProgramException(create_message(normal)) {
        
    }
    
};

class InvalidCharacterInMnemonicException : public ProgramException {
    
    static string create_message(char chr) {
        stringstream message;
        message<<"Character \""<<chr<<"\" cannot appear in mnemonic.";
        return message.str();
    }
    
public:
    
    InvalidCharacterInMnemonicException(char chr)
    :ProgramException(create_message(chr)) {
        
    }
    
};

class UnexpectedEndOfInstructionException : public ProgramException {
    
    static string create_message(string expected) {
        stringstream message;
        message<<"Unexpected end of instruction.";
        if(expected != "") {
            message<<" Expected "<<expected<<".";
        }
        return message.str();
    }
    
public:
    
    UnexpectedEndOfInstructionException(string expected)
    :ProgramException(create_message(expected)) {
        
    }
    
};

class InvalidCharactersInValueException : public ProgramException {
    
    static string create_message(char chr) {
        stringstream message;
        message<<"Invalid character \""<<chr<<"\""<<" in expression.";
        return message.str();
    }
    
public:
    
    InvalidCharactersInValueException(char chr)
    :ProgramException(create_message(chr)) {
        
    }
    
};

class InvalidImmediateSubstitutionException : public ProgramException {
    
    static string create_message(char escape_char, long value) {
        stringstream message;
        string immediateType;
        switch (escape_char) {
            case 'w':
                immediateType = "word";
                break;
                
            case 'b':
                immediateType = "byte";
                break;
                
            default:
                immediateType = "unrecognized type";
                break;
        }
        message<<"Number "<<value<<" cannot be substituted for immediate of type "<<immediateType;
        return message.str();
    }
    
public:
    
    InvalidImmediateSubstitutionException(char escape_char, long value)
    :ProgramException(create_message(escape_char, value))
    {
        
    }
    
};

#endif /* InstructionExceptions_h */
