//
//  EscapedBinary.cpp
//  z80asm
//
//  Created by Rafał Białek on 24/10/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#include "EscapedBinary.h"

EscapedBinary::EscapedBinary()
:resolved(NULL)
{
    
}

EscapedBinary::EscapedBinary(string hexEncoded)
:hexWithEscape(hexEncoded)
,resolved(NULL)
{
    
}

unsigned int EscapedBinary::length() {
    unsigned int length = 0;
    
    string::const_iterator iter = hexWithEscape.cbegin();
    string::const_iterator hex_end = hexWithEscape.cend();
    
    while ( iter != hex_end ) {
        char current = *iter;
        
        if ( current == '%' ) {
            char next = tolower(*(++iter));
            switch (next) {
                case 'w':
                    length += 2;
                    break;
                    
                case 'b':
                    length += 1;
                    break;
                    
                case '\0' :
                    assert(false);  //the string ends after % sign
                    break;
                    
                default:
                    assert(false); //either no char after % or wrong char
                    break;
            }
        }
        else if (isxdigit(current)) {
            char next = *(++iter);
            
            if ( iter == hex_end || !isxdigit(next) ) {
                assert(false);   //either half byte or invalid char
            }
            else {
                length += 1;
            }
        }
        iter++;
    }
    
    return length;
}

bool EscapedBinary::isResolved() {
    return resolved != NULL;
}

void EscapedBinary::resolve(list<long> immediates) {
    string::const_iterator iter = hexWithEscape.cbegin();
    string::const_iterator hex_end = hexWithEscape.cend();

    resolved = new string();
    
    while ( iter != hex_end ) {
        char current = *iter;
        
        if ( isxdigit(current) ) {
            (*resolved) += current;
        }
        else if ( current == '%' ) {
            char next = *(++iter);
            
            long immediate = immediates.front();    //if it fails something went wrong earlier
            
            if ( immediate < 0 ) {
                throw new InvalidImmediateSubstitutionException(next, immediate);
            }
            
            char substitution[10];
            
            switch (next) {
                case 'b':
                    if ( immediate > 0xFF ) {
                        throw new InvalidImmediateSubstitutionException(next, immediate);
                    }
                    sprintf(substitution, "%02lx", immediate);
                    break;
                    
                case 'w':
                {
                    if ( immediate > 0xFFFF ) {
                        throw new InvalidImmediateSubstitutionException(next, immediate);
                    }
                    long littleEndian = (immediate & 0x00FF) << 8 | (immediate & 0xFF00) >> 8;
                    
                    sprintf(substitution, "%04lx", littleEndian);
                    break;
                }
                    
                case '\0' :
                    assert(false);   //should not happen (length() took care of it?), the string ends after "%"
                    break;
                    
                default:
                    assert(false);     //should not happen (length() took care of it?), invalid char after "%"
                    break;
            }
            
            resolved->append(substitution);
            immediates.pop_front();
        }
        else {
            assert(false);   //Should not happen here, but I forgot why. Too lazy to check now. Sorry if it fails later.
        }
        iter++;
    }
}

string EscapedBinary::getResolved() {
    return *resolved;
}

char EscapedBinary::charToNum(char chr) {
    if(chr >= '0' && chr <= '9')
        return chr - '0';
    if(chr >= 'A' && chr <= 'F')
        return chr - 'A' + 10;
    if(chr >= 'a' && chr <= 'f')
        return chr - 'a' + 10;
    
    return 0;
}

EscapedBinary::~EscapedBinary() {
    if ( resolved != NULL ) {
        delete resolved;
    }
}
