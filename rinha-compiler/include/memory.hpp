#include "stack.hpp"
#include <map>
#include <string>
#include <vector>
#include <stack>
#include "symbol.hpp"

#ifndef MEMORY_HPP
#define MEMORY_HPP

namespace rinha_compiler{

    class Memory
    {
    private:
        std::vector<std::stack<std::vector<Type>>> men;
        void store(int scope, int addr, Type value);
        Type load(int scope, int addr);
    public:
        Memory();
        void store(Symbol symbol, Type value);
        Type load(Symbol symbol);
        void push(int scope);
        void pop(int scope);
        void increment(int size);
        ~Memory();
    };
}

#endif