#include <gtest/gtest.h>
#include <string.h>
#include "ast.hpp"
#include "parser_json_to_ast.hpp"
#include <daw/daw_read_file.h>
#include <filesystem>

// namespace {
// std::string_view GetData(const std::string& path)
// {



//     auto data = daw::read_file( path );
// 	//auto json_data = std::string_view( data.data( ), data.size( ) );

//     std::filesystem::path cwd = std::filesystem::current_path();
//     std::cout << "Current directory path: " << cwd << std::endl;
//     std::cout << "Current file path: " << __FILE__ << std::endl;

    
//     return data;
// }
// }
//INSTANTIATE_TEST_SUITE_P(Json, test_parser_json, GetTests("test_data/print.json"));

TEST(test_parser_json, test_parser_json_print)
{
    //std::string_view test_001_t_json_data = GetData("./tests/test_data/print.json");
    auto test_001_t_json_data = *daw::read_file( "./tests/test_data/print.json" );
    std::cout << test_001_t_json_data << std::endl;

    
    File file = json_to_ast::parser(test_001_t_json_data);
    
 
    ASSERT_EQ(21, file.location.end);
}