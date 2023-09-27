#include <symbol_table.hpp>
#include <rinha_exception.hpp>
#include <stack>
#include <interpreter.hpp>

extern rinha_compiler::FunctionCache function_cache;
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
                throw rinha_compiler::RinhaException("Simbolo " + id + ", não encontrado na tabela de simbolos.");
            }
            
            function_cache.set_change_scope(id);
        }
        throw rinha_compiler::RinhaException("Simbolo " + id + ", não encontrado na tabela de simbolos.");
    }

    Symbol SymbolTable::Put(std::string id, Symbol simbol){
        if(!table.contains(id))
        {
            simbol.index = size++;
            table.insert({id, simbol});
        }
        return Get(id);
    }

    SymbolTable* SymbolTable::GetParent(){
        return parent;
    }

    SymbolTable::~SymbolTable()
    {
    }
}