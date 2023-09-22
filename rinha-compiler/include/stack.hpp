#include <stack>
#include <variant>
#include <string>


#ifndef STACK_HPP
#define STACK_HPP

using Type = std::variant<int, bool, std::string>;

class stack
{
    private:
        std::stack<Type> st;
    public:
        void push(Type value);
        Type pop();
        ~stack();
};

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
    

#endif