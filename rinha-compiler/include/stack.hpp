#include <stack>
#include <variant>
#include <string>
#include <iostream>
#include <tuple>
#include <type.hpp>


#ifndef STACK_HPP
#define STACK_HPP

namespace rinha_compiler{
    class stack
    {
        private:
            std::stack<Type> st;
        public:
            void push(Type value);
            Type pop();
            ~stack();
    };
}

#endif