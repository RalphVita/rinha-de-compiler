#include <box.hpp>
#include <ast.hpp>
#ifndef _TYPE_HPP_
#define _TYPE_HPP_

namespace rinha_compiler{
    using Type = std::variant<int, bool, std::string, box<struct tupla>, Term>;
    struct tupla{
        std::tuple<Type,Type> value;  
    };
}

#endif