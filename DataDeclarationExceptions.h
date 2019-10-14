//
//  DataDeclarationExceptions.h
//  z80asm
//
//  Created by Rafał Białek on 11/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef DataDeclarationExceptions_h
#define DataDeclarationExceptions_h

class InvalidDataTypeException : public ProgramException {
    
    static string create_message(string symbol) {
        stringstream message;
        message<<"\""<<symbol<<"\" is not a recognised data type.";
        return message.str();
    }
    
public:
    
    InvalidDataTypeException(string type)
    :ProgramException(create_message(type))
    {
        
    }
};

class MalformedDataDeclarationException : public ProgramException {
    
    static string create_message(string line) {
        stringstream message;
        message<<"Line \""<<line<<"\" is not a valid data declaration.";
        return message.str();
    }
    
public:
    
    MalformedDataDeclarationException(string line)
    :ProgramException(create_message(line))
    {
        
    }
};

class InvalidValueForDataTypeException : public ProgramException {
    
    static string create_message(string value) {
        stringstream message;
        message<<"Value \""<<value<<"\" is invalid for specified type.";
        return message.str();
    }
    
public:
    
    InvalidValueForDataTypeException(string value)
    :ProgramException(create_message(value))
    {
        
    }
};

class UnclosedStringDeclarationException : public ProgramException {
    
public:
    
    UnclosedStringDeclarationException()
    :ProgramException("Unexpected end of declaration.")
    {
        
    }
};

#endif /* DataDeclarationExceptions_h */
