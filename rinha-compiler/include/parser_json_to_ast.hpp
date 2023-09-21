#include "ast.hpp"


#ifndef PARSER_JSON_TO_AST_HPP
#define PARSER_JSON_TO_AST_HPP

namespace json_to_ast {
File parser(std::string_view json_data);
}

#endif