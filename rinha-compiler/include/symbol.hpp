#include <string>
#include <ast.hpp>

#ifndef _SYMBOL_HPP_
#define _SYMBOL_HPP_

namespace rinha_compiler {
    using Symbol = struct _Symbol;
    Symbol init_symbol(std::string, int);
    Symbol init_symbol(std::string, int, Term);
    struct _Symbol{
        std::string id;
        int scope;
        int index;
        bool is_function;
        Term term;
    };
    
    
    
}
#endif