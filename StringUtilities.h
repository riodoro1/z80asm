//
//  StringUtilities.h
//  z80asm
//
//  Created by Rafał Białek on 09/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef StringUtilities_h
#define StringUtilities_h

#include <string>

namespace StringUtilities {
    
    /*
     Reads a number in base 2,10 or 16
     The number can be preceeded by 0b, 0d, 0x prefix, when no such prefix, base 10 is assumed
    */
    inline long readNumber(string::const_iterator &iterator, string::const_iterator &end, string *read) {
        if (iterator == end || !isdigit(*iterator)) {
            return 0;   //that's not a number...
        }
        
        char next = *(iterator+1);  //safe, '\0' in the worst case
        int base = 10;              //base 10 assumed
        
        switch (next) {
            case 'b':
                base = 2;
                iterator += 2;
                break;
                
            case 'd':
                base = 10;
                iterator += 2;
                break;
                
            case 'x':
                base = 16;
                iterator += 2;
                break;
                
            default:
                break;
        }
        
        if ( iterator == end ) {
            //this has only a chance to be visited when the iterator was shifted in the swich
            //end of line after base prefix
            return 0;
        }
        
        string::const_iterator digits_start = iterator;
        string digits;
        while ( iterator != end && ( isalpha(*iterator) || isnumber(*iterator) ) ) {
            digits+=*(iterator++);
        }
        
        if ( read != NULL ) {
            *read = digits;
        }
        
        char *parsed_end;
        long immediate_value = strtol(digits.c_str(), &parsed_end, base);
        unsigned long parsed_length = parsed_end - digits.c_str();
        
        if ( parsed_length != digits.size() ) {
            //invalid characters for base specified in immediate
            iterator = digits_start + parsed_length;
            return 0;
        }
        
        return immediate_value;
    }
    
    inline unsigned int ommitSpaces(string::const_iterator &iterator, string::const_iterator &end) {
        unsigned int counter = 0;
        
        while ( iterator != end && isspace(*iterator)) {
            counter++;
            iterator++;
        }
        
        return counter;
    }
    
}

#endif /* StringUtilities_h */
