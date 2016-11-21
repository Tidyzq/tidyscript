cmake_minimum_required(VERSION 3.6)
project(tidyscript)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

set(SOURCE_FILES
        include/lexer.hpp
        include/token.hpp src/token.cpp src/lexer.cpp src/parse_exception.cpp include/parse_exception.hpp)

add_executable(lexer_runner ${SOURCE_FILES} src/test/lexer_runner.cpp)