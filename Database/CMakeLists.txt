cmake_minimum_required(VERSION 3.15)
project(Relational_Database)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Relational_Database
        DatalogProgram.h
        main.cpp
        Parameter.h
        Parser.cpp
        Parser.h
        Predicate.h
        Rule.h
        Scanner.cpp
        Scanner.h
        Token.h Database.h Relation.cpp Relation.h Scheme.h Tuple.h Interpreter.cpp Interpreter.h)
