cmake_minimum_required(VERSION 3.22.1)
project(main "CXX")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

#find_package( daw-json-link )
include(CTest)
enable_testing()

add_subdirectory(tests)

include_directories(rinha-compiler)
add_subdirectory(rinha-compiler)
add_executable(${PROJECT_NAME} main.cpp)

# add_library(rinha2 SHARED "${CMAKE_CURRENT_SOURCE_DIR}/src/parser_json_to_ast.cpp")
# target_include_directories(rinha2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

# target_include_directories(rinha-compile PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")



target_link_libraries(${PROJECT_NAME} rinha-compiler)