#include "../include/symbol.hpp"
#include <string>

namespace rinha_compiler {
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