//
//  Data.c
//  z80asm
//
//  Created by Rafał Białek on 11/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#include "DataBlock.h"


#include <iostream>

DataBlock::DataBlock(string line)
:BinaryBlock(line)
{
    parse(line);
}


void DataBlock::readNumbers(string &line, string::const_iterator &iter, Type type) {
    
    string::const_iterator lineEnd = line.cend();
    
    while ( iter != lineEnd ) {
        string value;
        
        StringUtilities::ommitSpaces(iter, lineEnd);
        long number = StringUtilities::readNumber(iter, lineEnd, &value);
        StringUtilities::ommitSpaces(iter, lineEnd);
        
        if ( iter != lineEnd ) {
            if ( *iter !=',' )
                throw new MalformedDataDeclarationException(line);
            iter ++;        //ommit a comma
        }
        
        char hexNumber[5];
        
        switch (type) {
            case byteType:
                if ( number >= 0xFF )
                    throw new InvalidValueForDataTypeException(value);
                sprintf(hexNumber, "%02lx", number);
                break;
                
            case wordType: {
                if ( number >= 0xFFFF )
                    throw new InvalidValueForDataTypeException(value);
                long littleEndian = (number & 0x00FF) << 8 | (number & 0xFF00) >> 8;
                sprintf(hexNumber, "%04lx", littleEndian);
                break;
            }
                
            default:
                assert(false); //how did we get here?
                break;
        }
        
        hexString.append(hexNumber);
    }
}

void DataBlock::readString(string &line, string::const_iterator &iter) {
    
    string::const_iterator lineEnd = line.cend();
    
    StringUtilities::ommitSpaces(iter, lineEnd);
    
    if ( iter == lineEnd || *iter != '\"' )
        throw new MalformedDataDeclarationException(line);

    iter ++;    //ommit "
    
    string str;
    
    while ( *iter != '\"' ) {
        if ( iter == lineEnd )
            throw UnclosedStringDeclarationException();
        
        char read = *iter++;
        
        if( read != '\\' ) {
            str += read;
        }
        else {
            char next = *iter;
            if ( next == '\"' ) {
                str += '\"';
                iter++;
            }
            else {
                str += '\\';
            }
        }
    }
    
    iter ++;    //ommit "
    
    StringUtilities::ommitSpaces(iter, lineEnd);
    
    if ( iter != lineEnd )
        throw new MalformedDataDeclarationException(line);
    
    
    for (string::const_iterator i = str.cbegin(); i != str.cend(); i++) {
        char hexChar[3];
        sprintf(hexChar, "%02x", (short)*i);
        hexString.append(hexChar);
    }
}


void DataBlock::parse(string line) {
    string::const_iterator iter = line.cbegin();
    string::const_iterator lineEnd = line.cend();
    
    StringUtilities::ommitSpaces(iter, lineEnd);
    
    if ( iter == lineEnd  || *iter != '.' )
        throw new MalformedDataDeclarationException(line);
    
    iter ++;    //skip the dot
    
    Type dataType = getType(iter, lineEnd);
    
    if ( iter == lineEnd || !isspace(*iter) )
        throw new MalformedDataDeclarationException(line);
    
    StringUtilities::ommitSpaces(iter, lineEnd);
    
    if ( iter == lineEnd )
        throw new MalformedDataDeclarationException(line);
    
    //parse the data itself
    switch (dataType) {
        case byteType:
        case wordType:
            readNumbers(line, iter, dataType);
            break;
            
        case stringType:
            readString(line, iter);
            break;
    }
}

DataBlock::Type DataBlock::getType(string::const_iterator &iter, string::const_iterator lineEnd) {
    string typeString;
    
    while(iter != lineEnd && isalpha(*iter)) {
        typeString += tolower((*iter++));
    }
    
    if ( typeString == "byte" )
        return byteType;
    else if ( typeString == "word" )
        return wordType;
    else if ( typeString == "string" )
        return stringType;
    else
        throw new InvalidDataTypeException(typeString);
}

unsigned int DataBlock::getLength() {
    assert(hexString.length() % 2 == 0);
    return hexString.length()/2;
}

string DataBlock::getHexString() {
    return hexString;
}
