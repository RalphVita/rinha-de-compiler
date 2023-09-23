#include <map>
#include <string>
#include <iostream>
#include <memory>

#ifndef SYMBOL_HPP
#define SYMBOL_HPP
namespace rinha_compiler {
    struct Symbol{
        std::string id;
        //std::string type;
        int scope;
        int index;
        Symbol(std::string _id, int _scope, int _index):id(_id), scope(_scope), index(_index){}
    };
}
#endif