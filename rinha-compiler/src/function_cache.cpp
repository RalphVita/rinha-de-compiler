#include <function_cache.hpp>
#include <rinha_exception.hpp>
#include <type.hpp>
#include <ast.hpp>
#include <stack>

namespace rinha_compiler {
    FunctionCache::FunctionCache(){
        function_out_scope_stack.push(true);
        function_name_stack.push("_");
    }

    void FunctionCache::input_function(std::string function_name){
        function_out_scope_stack.push(false);
        function_name_stack.push(function_name);
    }
    void FunctionCache::output_function(){
        function_out_scope_stack.pop();
        function_name_stack.pop();
    }

    bool FunctionCache::function_can_have_cache(){
        return !(function_out_scope_stack.top());
    }
    void FunctionCache::set_change_scope(std::string id){
         if(id != function_name_stack.top())
            function_out_scope_stack.top() = true;
    }

    void FunctionCache::push_parameters(Type value){
        parameters.push(value);
        count_parameters++;
    }
    std::string FunctionCache::hash_args(){

        struct to_string_visit
        {
            std::string operator()(std::string x){ return x;}
            std::string operator()(bool x){ return (x ? "true": "false");}
            std::string operator()(int x){ return std::to_string(x);}
            std::string operator()(box<tupla> &x){ 
                std::string y = "("; 
                y += std::visit(*this, std::get<0>(x->value));
                y +=  ", "; 
                y +=  std::visit(*this, std::get<1>(x->value));
                y +=  ")";
            }
            std::string operator()(Term &x){
                throw rinha_compiler::RinhaException("Tipo de argumento inválido para hash_args.");
                return "";
            }
        };

        std::string hash = "";
        for (int i = count_parameters - 1; i >= 0; i--){
            hash += std::visit(to_string_visit{}, parameters.top());
            parameters.pop();
            count_parameters--;
        }
        return hash;
    }

    bool FunctionCache::has_value(std::string hash){
        std::string function_name = this->function_name_stack.top();
        auto func = func_cache.find(function_name);
        if(func == func_cache.end())
            return false;

        if(func->second.find(hash) == func->second.end())
            return false;

        return true;
    }

    void FunctionCache::set_value(std::string hash, Type value)
    {
        std::string function_name = this->function_name_stack.top();
        auto func = func_cache.find(function_name);
        if(func == func_cache.end())
        {
            std::map<std::string, Type> inner;
            inner.insert({hash, value});
            func_cache.insert({function_name, inner});
        }else{
            if(func->second.find(hash) == func->second.end()){
                func->second.insert({hash, value});
            }
        }
    }

    Type FunctionCache::get_value(std::string hash)
    {
        std::string function_name = this->function_name_stack.top();
        return func_cache.find(function_name)->second.find(hash)->second;
    }
}