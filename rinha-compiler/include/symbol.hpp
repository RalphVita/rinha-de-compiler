#include <map>
#include <string>
#include <iostream>
#include <memory>
#include "box.hpp"
#include "ast.hpp"

#ifndef SYMBOL_HPP
#define SYMBOL_HPP
namespace rinha_compiler {
    struct Symbol{
        std::string id;
        //std::string type;
        int scope;
        int index;
        Term term;
        //Symbol(std::string _id, int _scope, int _index):id(_id), scope(_scope), index(_index), function(){}
    };
    Symbol init_symbol(std::string id, int scope){
        Symbol symbol;
        symbol.id = id;
        symbol.scope = scope;

        return symbol;
    }
    Symbol init_symbol(std::string id, int scope, Term term){
        Symbol symbol = init_symbol(id, scope);
        symbol.term = term;

        return symbol;
    }
}
#endif