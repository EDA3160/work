cmake_minimum_required(VERSION 3.22)
project(project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

aux_source_directory("database" SRC_LIST0)
aux_source_directory("exporter" SRC_LIST1)
aux_source_directory("placement" SRC_LIST2)
aux_source_directory("parser" SRC_LIST4)

include_directories("database" "exporter" "parser" "placement")

add_executable(project main.cpp ${SRC_LIST0} ${SRC_LIST1} ${SRC_LIST2} ${SRC_LIST4})

find_package(nlohmann_json REQUIRED)
target_link_libraries(project nlohmann_json::nlohmann_json)

add_library(json_includes INTERFACE)
target_include_directories(json_includes INTERFACE ${NLOHMANN_JSON_INCLUDE_DIRS})


