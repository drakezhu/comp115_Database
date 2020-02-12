cmake_minimum_required(VERSION 3.9)
project(a4)

set(CMAKE_CXX_STANDARD 11)

add_executable(a4
        ColumnNames.cpp
        ColumnNames.h
        Database.cpp
        Database.h
        RelationalAlgebra.cpp
        RelationalAlgebra.h
        Row.cpp
        Row.h
        Table.cpp
        Table.h
        dbexceptions.h
        main.cpp
        test.cpp
        unittest.cpp
        unittest.h
        RowCompare.cpp
        RowCompare.h)
