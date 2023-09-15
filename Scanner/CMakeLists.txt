cmake_minimum_required(VERSION 3.15)
project(Scanner)

set(CMAKE_CXX_STANDARD 17)

add_executable(Scanner main.cpp Scanner.cpp Scanner.h Token.h)