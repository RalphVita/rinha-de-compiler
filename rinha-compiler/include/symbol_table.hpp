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
        std::unique_ptr<SymbolTable> parent;
        std::map<std::string, Symbol> table;
        int size;
    public:
        SymbolTable();
        SymbolTable(std::unique_ptr<SymbolTable> &parent);
        void Put(std::string id, Symbol simbol);
        Symbol Get(std::string id);
        std::unique_ptr<SymbolTable> GetParent();
        ~SymbolTable();
    };
}

#endif