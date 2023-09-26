#include <sstream>
#include <iostream>
#include <string>
#include <daw/daw_read_file.h>
#include <rinha-compiler.hpp>
using namespace std;
std::ostringstream oss;
std::streambuf* p_cout_streambuf = std::cout.rdbuf();

void test_let_bool(File);
void test_let_int(File);
void test_let_str(File);
void test_let_tuple(File);
void test_first_second(File);
void test_if(File);
void test_else(File);
void test_sum_print(File);
void test_nested_print(File);
void test_nested_print_tuple(File);

int main(int argc, char **argv ){

    
    std::cout.rdbuf(oss.rdbuf());

    std::string test_name = argv[1];
    std::string path = argv[2];

    auto json_data = *daw::read_file( path );
    File file = json_to_ast::parser(json_data);

    
    

    if(test_name == "test_let_bool")
        test_let_bool(file);
    else if(test_name == "test_let_int")
        test_let_int(file);
    else if(test_name == "test_let_str")
        test_let_str(file);
    else if(test_name == "test_let_tuple")
        test_let_tuple(file);
    else if(test_name == "test_first_second")
        test_first_second(file);
    else if(test_name == "test_if")
        test_if(file);
    else if(test_name == "test_else")
        test_else(file);
    else if(test_name == "test_sum_print")
        test_sum_print(file);
    else if(test_name == "test_nested_print")
        test_nested_print(file);
    else if(test_name == "test_nested_print_tuple")
        test_nested_print_tuple(file);

    std::cout.rdbuf(p_cout_streambuf);
    
    return 0;
}

void test_let_bool(File file){
    auto expected = "true\n";

    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}

void test_let_int(File file){
    auto expected = "1\n";
    
    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}

void test_let_str(File file){
    auto expected = "texto\n";

    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}

void test_let_tuple(File file){
    auto expected = "(55, (Text, (true, false)))\n";

    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}

void test_first_second(File file){
    auto expected = "(true, 1)\n";

    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}

void test_if(File file){
    auto expected = "if\n";

    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}
void test_else(File file){
    auto expected = "else\n";

    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}

void test_sum_print(File file){
    auto expected = "1\n2\n3\n";

    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}
void test_nested_print(File file){
    auto expected = "1\n2\n2\n";

    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}
void test_nested_print_tuple(File file){
    auto expected = "1\n2\n(1, 2)\n";

    interpreter::walk(file);
    
    assert(oss && oss.str() == expected);
}