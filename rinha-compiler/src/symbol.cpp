#include "../include/symbol.hpp"
#include <string>

namespace rinha_compiler {
    Symbol init_symbol(std::string id, int scope){
        Symbol symbol;
        symbol.id = id;
        symbol.scope = scope;
        symbol.is_function = false;

        return symbol;
    }

    Symbol init_symbol(std::string id, int scope, Term term){
        Symbol symbol = init_symbol(id, scope);
        symbol.is_function = true;
        symbol.term = term;

        return symbol;
    }
}