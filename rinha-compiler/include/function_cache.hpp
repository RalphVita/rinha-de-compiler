#include <rinha_exception.hpp>
#include <type.hpp>
#include <stack>

#ifndef FUNCTION_CACHE_HPP
#define FUNCTION_CACHE_HPP

namespace rinha_compiler {
class FunctionCache{
        private:
            std::map<std::string, std::map<std::string, Type>> func_cache;
            std::stack<Type> parameters;
            int count_parameters = 0;
            std::stack<bool> function_out_scope_stack;
            std::stack<std::string> function_name_stack;
        
        public:
            FunctionCache();

            void input_function(std::string);
            void output_function();

            bool function_can_have_cache();
            void set_change_scope(std::string);

            void push_parameters(Type);
            std::string hash_args();
            bool has_value(std::string);
            void set_value(std::string, Type );
            Type get_value(std::string );
    };
}
#endif