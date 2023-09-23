#include <symbol_table.hpp>



namespace rinha_compiler{

    SymbolTable::SymbolTable(){
        size = 0;
        has_parent = false;
    }
    SymbolTable::SymbolTable(SymbolTable* parent)
    {
        this->parent = parent;   
        size = 0;
        has_parent = true;
    }

    Symbol SymbolTable::Get(std::string id){
        for(SymbolTable* st = this; st != nullptr; st = st->parent){
            trace("---Get---");
            trace(st->table.size());
            auto simbol = st->table.find(id);
            
            if(simbol != st->table.end())
                return simbol->second;
            if(!st->has_parent){
                trace(id);
                throw 555;
            }
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