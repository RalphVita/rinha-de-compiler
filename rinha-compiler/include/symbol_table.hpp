#include <map>
#include <string>
#include <iostream>
#include <memory>
#include "symbol.hpp"


#ifndef SYMBOL_TABLE_HPP
#define SYMBOL_TABLE_HPP

namespace rinha_compiler{
    class SymbolTable
    {
    private:
        SymbolTable* parent;
        std::map<std::string, Symbol> table;
        int size;
        bool has_parent = false;;
    public:
        SymbolTable();
        SymbolTable(SymbolTable* parent);
        void Put(std::string id, Symbol simbol);
        Symbol Get(std::string id);
        SymbolTable* GetParent();
        ~SymbolTable();
    };
}

#endif