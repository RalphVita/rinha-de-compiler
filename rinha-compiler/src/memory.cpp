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
            //Aloca espaço, caso não tenha o sufuciente
            if(men[scope].top().size() <= addr)
                men[scope].top().resize(addr + 3);

            men[scope].top()[addr] = value;
    }

    Type Memory::load(Symbol symbol){
        return this->load(symbol.scope, symbol.index);
    }

    Type Memory::load(int scope, int addr){
        return men[scope].top()[addr];
    }

    void Memory::push(int scope){
        std::vector<Type> vt(3);//TODO: Retornar endereço, em vez de tamanho fixo.
        men[scope].push(vt);
    }
    void Memory::pop(int scope){
        men[scope].pop();
    }

    Memory::~Memory()
    {
    }
}

