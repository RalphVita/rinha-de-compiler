cmake_minimum_required(VERSION 3.22.1)

#project(rinha-compiler-test "CXX")


#include_directories(rinha-compiler)
#include_directories(rinha-compiler/include)
#add_subdirectory(rinha-compiler)

#enable_testing()

add_executable(parser_json_to_ast_test src/parser_json_to_ast_test.cpp )
target_include_directories(parser_json_to_ast_test PUBLIC "${CMAKE_SOURCE_DIR}/rinha-compiler")
#target_link_libraries(parser_json_to_ast_test rinha-compiler)
target_link_libraries(parser_json_to_ast_test PUBLIC rinha-compiler )
add_test(NAME test_parser_json_print COMMAND parser_json_to_ast_test "test_parser_json_print" "${CMAKE_SOURCE_DIR}/tests/test_data/print.json")


# # set(CMAKE_CXX_STANDARD 20)
# # set(CMAKE_CXX_STANDARD_REQUIRED ON)
# # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")


# # find_package( daw-json-link )

# include(FetchContent)

# FetchContent_Declare(
#   googletest
#   GIT_REPOSITORY https://github.com/google/googletest.git
#   GIT_TAG        release-1.11.0
# )
# FetchContent_MakeAvailable(googletest)
# add_library(GTest::GTest INTERFACE IMPORTED)
# target_link_libraries(GTest::GTest INTERFACE gtest_main)

# file(GLOB sources "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# #message("${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
# add_executable(rinha-test ${sources})
# #target_include_directories(rinha PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# target_link_libraries(rinha-test
# PRIVATE
#   GTest::GTest
#   rinha2)

# # target_link_libraries(rinha daw::daw-json-link )
# add_test(
#     NAME rinha-test
#     COMMAND rinha-test
#     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#     )
