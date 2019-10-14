//
//  ProgramException.h
//  z80asm
//
//  Created by Rafał Białek on 02/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef ProgramException_h
#define ProgramException_h

#include <exception>
#include <string>
#include <sstream>
using namespace std;

class ProgramException : protected runtime_error {
    bool _hasLine;
    unsigned int _line;
    
public:
    ProgramException(string message)
    :runtime_error(message)
    ,_hasLine(false)
    {
        
    }
    
    ProgramException(string message, unsigned int line)
    :runtime_error(message)
    ,_hasLine(true)
    ,_line(line)
    {
        
    }
    
    void setLine(unsigned int line) {
        _hasLine = true;
        _line = line;
    }

    bool hasLine() {
        return _hasLine;
    }

    unsigned int line() {
        return _line;
    }
    
    const char *getMessage() {
        return what();
    }
};

#endif /* ProgramException_h */
