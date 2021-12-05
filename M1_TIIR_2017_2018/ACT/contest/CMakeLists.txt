cmake_minimum_required(VERSION 3.3)
project(contest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#set(BUILD_1 main)
#set(SOURCE_FILES_1 plus_longue_sous_suite_croissante.cpp)
#add_executable(${BUILD_1} ${SOURCE_FILES_1})

set(BUILD_2 main)
set(SOURCE_FILES_2 bouteilles.cpp)
add_executable(${BUILD_2} ${SOURCE_FILES_2})