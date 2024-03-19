cmake_minimum_required(VERSION 3.22)
project(project)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


aux_source_directory("parser" SRC_LIST)
aux_source_directory("database" SRC_LIST1)
add_executable(project main.cpp ${SRC_LIST1} ${SRC_LIST})

include_directories("database" "parser")

target_include_directories(project
        PRIVATE "parser"
        PRIVATE "database")


