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
        //std::string type;
        int scope;
        int index;
        Term term;
        //Symbol(std::string _id, int _scope, int _index):id(_id), scope(_scope), index(_index), function(){}
    };
    
    
    
}
#endif