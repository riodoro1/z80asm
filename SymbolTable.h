//
//  SymbolTable.h
//  z80asm
//
//  Created by Rafał Białek on 02/11/2016.
//  Copyright © 2016 Rafał Białek. All rights reserved.
//

#ifndef SymbolTable_h
#define SymbolTable_h

#include <string>
#include <unordered_map>

#include "Exceptions.h"

using namespace std;

class SymbolTable {
    typedef pair<string, long> Entry;
    typedef unordered_map<string, long> Table;
    Table table;
    
public:
    
    SymbolTable() {
        
    }
    
    void declareSymbol(string name, long value) {
        Entry entry = make_pair(name, value);
        
        pair<Table::iterator, bool> result = table.insert(entry);
        
        if(!result.second) {
            throw new SymbolRedeclarationException(name);
        }
    }
    
    long getValue(string symbol) {
        try {
            return table.at(symbol);
        } catch (out_of_range e) {
            throw new SymbolNotFoundException(symbol);
        }
    }
};

#endif /* SymbolTable_h */
