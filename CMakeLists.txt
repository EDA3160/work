cmake_minimum_required(VERSION 3.22)
project(project)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_LINK_FLAGS "-static" )

#find_package(nlohmann_json CONFIG REQUIRED)
#target_link_libraries(project PRIVATE nlohmann_json::nlohmann_json)
#target_link_libraries(main PRIVATE nlohmann_json::nlohmann_json)
#
#
#set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
#        CACHE STRING "Vcpkg toolchain file")



aux_source_directory("database" SRC_LIST0)
aux_source_directory("exporter" SRC_LIST1)
aux_source_directory("placement" SRC_LIST2)
aux_source_directory("parser" SRC_LIST4)

add_executable(project main.cpp  ${SRC_LIST0} ${SRC_LIST1} ${SRC_LIST2} ${SRC_LIST4}
        exporter/exporter.cpp
        exporter/exporter.h)

include_directories("database" "parser"  "parser"  "placement")

