#include "stack.hpp"
#include <map>
#include <string>
#include <vector>
#include <stack>
#include "Symbol.hpp"
//#include <ast.hpp>

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
        void init(int size);
        void store(Symbol symbol, Type value);
        Type load(Symbol symbol);
        void push(int scope);
        void pop(int scope);
        ~Memory();
    };

    Memory::Memory(){}
    void Memory::init(int size)
    {
        men.reserve(size);
    }

    void Memory::store(Symbol symbol, Type value){
        this->store(symbol.scope, symbol.index, value);
    }

    void Memory::store(int scope, int addr, Type value){
            men[scope].top()[addr] = value;
    }

    Type Memory::load(Symbol symbol){
        return this->load(symbol.scope, symbol.index);
    }

    Type Memory::load(int scope, int addr){
        return men[scope].top()[addr];
    }

    void Memory::push(int scope){
        std::vector<Type> vt(1000);//TODO
        men[scope].push(vt);
    }
    void Memory::pop(int scope){
        men[scope].pop();
    }

    Memory::~Memory()
    {
    }
}

#endif