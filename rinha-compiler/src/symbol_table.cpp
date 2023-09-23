#include <symbol_table.hpp>



namespace rinha_compiler{

    SymbolTable::SymbolTable(){
        size = 0;
    }
    SymbolTable::SymbolTable(SymbolTable* parent)
    {
        parent = parent;   
        size = 0;
    }

    Symbol SymbolTable::Get(std::string id){
        for(SymbolTable* st = this; st != nullptr; st = st->parent){
            auto simbol = st->table.find(id);
            if(simbol != st->table.end())
                return simbol->second;
            st = st->parent;
        }
        throw 555;
    }

    void SymbolTable::Put(std::string id, Symbol simbol){
        if(!table.contains(id))
        {
            simbol.index = size++;
            table.insert({id, simbol});
        }
    }

    SymbolTable* SymbolTable::GetParent(){
        return parent;
    }

    SymbolTable::~SymbolTable()
    {
    }
}