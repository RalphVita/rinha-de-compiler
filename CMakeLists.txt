cmake_minimum_required(VERSION 3.0)
project(main "CXX")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++20")

include( FetchContent )
FetchContent_Declare(
  daw_json_link
  GIT_REPOSITORY https://github.com/beached/daw_json_link
  GIT_TAG release
)
FetchContent_MakeAvailable(daw_json_link)

#include(CTest)
#enable_testing()

add_subdirectory(tests)

include_directories(rinha-compiler)
add_subdirectory(rinha-compiler)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC rinha-compiler)