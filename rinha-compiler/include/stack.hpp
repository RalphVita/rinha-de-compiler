#include <stack>
#include <variant>
#include <string>
#include <iostream>
#include <tuple>


#ifndef STACK_HPP
#define STACK_HPP

//using Type = std::variant<int, bool, std::string>;
//struct tupla;

//using Type = std::variant<int, bool, std::string>;

//using Type = std::variant<int, bool, std::string, std::tuple<int,int>>;
using Type = std::variant<int, bool, std::string, box<struct tupla>>;
struct tupla{
    std::tuple<Type,Type> value;  
    //int i;
};

//Type2 z;
// //template <typename T> // note, might as well take p as const-reference
// std::ostream& dump(std::ostream &o, const tupla& p)
// {
//     o << "(" << p.value.first << ", " << p.value.second << ")";
//     return o;
//     //return o << "(" << p.value << ", " << p.value << ")" << std::endl;
// }

//inline tupla::~tupla() = default;

// struct point{
//   int x, y;
//   void set(int x1,int y1){
//       x = x1,y=y1;
//   }
// };



// std::ostream& operator << (std::ostream& o, box<tupla>& a)
// {
//     //o << "(" << a.value.first << ", " << a.value.second << ")";
//     o << "(";
//     std::visit([](const auto &x) { std::cout << x << std::endl; }, a.value.first);
//     //o << "x: " << a.x << "\ty: " << a.y << std::endl;
    
//     return o;
// }


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