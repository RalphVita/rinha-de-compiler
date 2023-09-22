#include <string>
#include <string_view>
#include <vector>
#include <iostream>
#include <typeinfo>
#include <map>
#include <box.hpp>
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

struct Int
{
  std::string kind{};
  int value;
  Location location;
};

struct Bool
{
  std::string kind{};
  bool value;
  Location location;
};

using Term = std::variant<Int,
                          Str,
                          box<struct Call>,
                          box<struct Binary>,
                          box<struct Function>, 
                          box<struct Let>, 
                          box<struct If>, 
                          box<struct Print>,
                          box<struct First>,
                          box<struct Second>,
                          Bool,
                          box<struct Tuple>,
                          box<struct Var>
                        >;

struct Print
{
    std::string kind{};
    Term value;
    Location location;
};

struct Parameter{
  std::string text{};
  Location location;
};

struct Var
{
    std::string kind{};
    std::string text{};
    Location location;
};

struct Function
{
    std::string kind{};
    std::vector<Parameter> parameters;
    Term value;
    Location location;
};

struct Call
{
    std::string kind{};
    Term callee;
    std::vector<Term> arguments;
    Location location;
};

struct Let
{
    std::string kind{};
    Parameter name;
    Term value;
    Term next;
    Location location;
};

struct Binary {
  std::string kind{};
  Term lhs;
  std::string op{};
  Term rhs;
  Location location;
};

struct If {
  std::string kind{};
  Term condition;
  Term then;
  Term otherwise;
  Location location;
};

struct Tuple {
  std::string kind{};
  Term first;
  Term second;
  Location location;
};

struct First
{
    std::string kind{};
    Term value;
    Location location;
};

struct Second
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