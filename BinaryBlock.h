//
//  BinaryBlock.h
//  z80asm
//
//  Created by Rafał Białek on 09/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef BinaryBlock_h
#define BinaryBlock_h

#include <string>
using namespace std;

class BinaryBlock {
    string declaration;
public:
    BinaryBlock(string declaration) : declaration(declaration){};
    
    virtual unsigned int getLength() = 0;
    virtual string getHexString() = 0;
    
    string getDeclaration() {
        return declaration;
    }
};

#endif /* BinaryBlock_h */
