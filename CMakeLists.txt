cmake_minimum_required(VERSION 3.22)
project(project)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_LINK_FLAGS "-static" )

aux_source_directory("database" SRC_LIST0)
aux_source_directory("exporter" SRC_LIST1)
aux_source_directory("placement" SRC_LIST2)
aux_source_directory("parser" SRC_LIST4)

add_executable(project main.cpp  ${SRC_LIST0} ${SRC_LIST1} ${SRC_LIST2} ${SRC_LIST4})

include_directories("database" "parser"  "parser"  "placement")

# target_include_directories(project
#         PRIVATE "parser"
#         PRIVATE "database")


