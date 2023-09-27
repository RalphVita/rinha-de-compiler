#include <stack.hpp>

namespace rinha_compiler{
    
    void stack::push(Type value)
    {
        st.push(value);
    }
    Type stack::pop(){
        Type value = st.top();
        st.pop();
        return value;
    }

    stack::~stack()
    {
        //std::cout << "STACK Morreu" << std::endl;
    }
}