#include <symbol_table.hpp>
#include <iostream>
#include <memory>


namespace rinha_compiler{

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