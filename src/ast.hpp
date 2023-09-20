#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>
#include "box.hpp"
#include <variant>

#ifndef AST_HPP
#define AST_HPP
struct Location
{
    int start = 0;
    int end = 0;
    std::string filename{};
};

struct Str
{
  std::string kind{};
  std::string value{};
  Location location;
};

using Term = std::variant<Str,box<struct Print>>;

struct Print
{
    std::string kind{};
    Term value;
    Location location;
};

struct File{
  std::string name{};
  Term expression;
  Location location;
};

#endif