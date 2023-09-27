#include <memory.hpp>

namespace rinha_compiler{

    Memory::Memory(){
        men.reserve(1);
    }

    void Memory::increment(int size)
    {
        if(size > men.size())
            men.resize(size);
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
        std::vector<Type> vt(1000);//TODO: Aumentar a medida que for preciso
        men[scope].push(vt);
    }
    void Memory::pop(int scope){
        men[scope].pop();
    }

    Memory::~Memory()
    {
    }
}

