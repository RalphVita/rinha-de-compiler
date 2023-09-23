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

    SymbolTable::SymbolTable(){
        this->parent = nullptr;
        size = 0;
    }
    SymbolTable::SymbolTable(std::unique_ptr<SymbolTable> &parent)
    {
        this->parent = std::move(parent);   
        size = 0;
    }

    Symbol SymbolTable::Get(std::string id){
        for(std::unique_ptr<SymbolTable> st = std::unique_ptr<SymbolTable>(this); st != nullptr; st->parent){
            auto simbol = st->table.find(id);
            if(simbol != st->table.end())
                return simbol->second;
        }
        throw 555;
    }

    void SymbolTable::Put(std::string id, Symbol simbol){
        simbol.index = size++;
        table.insert({id, simbol});
    }

    std::unique_ptr<SymbolTable> SymbolTable::GetParent(){
        return std::move(this->parent);
    }

    SymbolTable::~SymbolTable()
    {
    }
}

#endif