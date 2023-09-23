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
    };
}
#endif