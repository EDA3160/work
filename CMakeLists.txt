cmake_minimum_required(VERSION 3.22)
project(project)

include_directories(database parser )

aux_source_directory(parser SRC_LIST)
aux_source_directory(database SRC_LIST1)
#aux_source_directory(placement SRC_LIST1)
#aux_source_directory(exporter SRC_LIST2)

add_executable(project main.cpp ${SRC_LIST1} ${SRC_LIST} )

