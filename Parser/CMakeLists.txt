cmake_minimum_required(VERSION 3.15)
project(Parser)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Parser
        .idea/deployment.xml
        .idea/misc.xml
        .idea/modules.xml
        .idea/Scanner.iml
        .idea/workspace.xml
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/Scanner.cbp
        cmake-build-debug/Scanner.exe
        main.cpp
        Scanner.cpp
        Scanner.h
        Token.h Parser.cpp Parser.h Predicate.h Rule.h Parameter.h DatalogProgram.h)
