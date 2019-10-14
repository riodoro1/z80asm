//
//  Data.h
//  z80asm
//
//  Created by Rafał Białek on 11/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef Data_h
#define Data_h

#include <string>

#include <assert.h>

#include "Exceptions.h"
#include "BinaryBlock.h"
#include "StringUtilities.h"

class DataBlock : public BinaryBlock {
    enum Type {
        byteType,
        wordType,
        stringType
    };
    
    string hexString;
    
    void readNumbers(string &line, string::const_iterator &iter, Type type);
    void readString(string &line, string::const_iterator &iter);
    
    Type getType(string::const_iterator &iter, string::const_iterator lineEnd);
    void parse(string line);
    
public:
    
    DataBlock(string line);
    
    unsigned int getLength();
    string getHexString();
    
};

#endif /* Data_h */
