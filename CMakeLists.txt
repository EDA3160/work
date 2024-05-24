cmake_minimum_required(VERSION 3.22)
project(project)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

aux_source_directory("database" SRC_LIST0)
aux_source_directory("exporter" SRC_LIST1)
aux_source_directory("placement" SRC_LIST2)
aux_source_directory("parser" SRC_LIST4)



include_directories("database" "exporter" "parser" "placement")
find_package(nlohmann_json 3.10.0 REQUIRED)
include_directories(${nlohmann_json_INCLUDE_DIRS})

 
add_executable(project main.cpp  ${SRC_LIST0} ${SRC_LIST1} ${SRC_LIST2} ${SRC_LIST4})
target_link_libraries(project ${nlohmann_json_INCLUDE})

#find_package(nlohmann_json CONFIG REQUIRED)
#target_link_libraries(project PRIVATE nlohmann_json::nlohmann_json)

