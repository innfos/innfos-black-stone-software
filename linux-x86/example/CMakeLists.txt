﻿cmake_minimum_required(VERSION 3.0)

project(EXAMPLE)


SET(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../innfos-cpp-sdk/sdk/lib/linux_x86_64)
link_directories(${LIB_DIR})
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/lib)

SET(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../innfos-cpp-sdk/sdk/include)
include_directories(${INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../sdk/include)

add_compile_options(-std=c++11)
add_compile_options(-fPIC)
add_compile_options(-pthread)
add_compile_options(-DASIO_STANDALONE)
add_compile_options(-DASIO_HAS_STD_CHRONO)

SET(EXAMPLE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/basic)
ADD_EXECUTABLE(mode0 ${EXAMPLE_SOURCES}/basic/mode0.cpp)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin/advanced)
ADD_EXECUTABLE(mode1 ${EXAMPLE_SOURCES}/advanced/mode1.cpp)
ADD_EXECUTABLE(mode2 ${EXAMPLE_SOURCES}/advanced/mode2.cpp)
ADD_EXECUTABLE(mode3 ${EXAMPLE_SOURCES}/advanced/mode3.cpp)
ADD_EXECUTABLE(mode4 ${EXAMPLE_SOURCES}/advanced/mode4.cpp)
target_link_libraries(mode0 kdl pthread ActuatorController)
target_link_libraries(mode1 kdl pthread ActuatorController)
target_link_libraries(mode2 kdl pthread ActuatorController)
target_link_libraries(mode3 kdl pthread ActuatorController)
target_link_libraries(mode4 kdl pthread ActuatorController)
