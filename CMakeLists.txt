cmake_minimum_required(VERSION 3.22)
project(project)

include_directories(database parser placement exporter)

aux_source_directory(parser SRC_LIST)
aux_source_directory(placement SRC_LIST1)
aux_source_directory(exporter SRC_LIST2)



