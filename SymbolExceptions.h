//
//  SymbolTableExceptions.h
//  z80asm
//
//  Created by Rafał Białek on 02/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef SymbolTableExceptions_h
#define SymbolTableExceptions_h

#include "ProgramException.h"

class SymbolNotFoundException : public ProgramException {
    
    static string create_message(string symbol) {
        stringstream message;
        message<<"Symbol \""<<symbol<<"\" was not defined in program.";
        return message.str();
    }
    
public:
    
    SymbolNotFoundException(string symbol)
    :ProgramException(create_message(symbol))
    {
        
    }
};

class MalformedSymbolDeclarationException : public ProgramException {
    
    static string create_message(string symbol) {
        stringstream message;
        message<<"\""<<symbol<<"\" is not a valid symbol declaration.";
        return message.str();
    }
    
public:
    
    MalformedSymbolDeclarationException(string declaration)
    :ProgramException(create_message(declaration))
    {
        
    }
};

class SymbolRedeclarationException : public ProgramException {
    
    static string create_message(string symbol) {
        stringstream message;
        message<<"Redeclaration of \""<<symbol<<"\".";
        return message.str();
    }
    
public:
    
    SymbolRedeclarationException(string symbol)
    :ProgramException(create_message(symbol))
    {
        
    }
};

#endif /* SymbolTableExceptions_h */
