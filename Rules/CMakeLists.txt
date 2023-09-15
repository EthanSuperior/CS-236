cmake_minimum_required(VERSION 3.15)
project(Rules)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Rules
        Database.h
        DatalogProgram.h
        Interpreter.cpp
        Interpreter.h
        main.cpp
        Parameter.h
        Parser.cpp
        Parser.h
        Predicate.h
        Relation.cpp
        Relation.h
        Rule.h
        Scanner.cpp
        Scanner.h
        Scheme.h
        Token.h
        Tuple.h)
