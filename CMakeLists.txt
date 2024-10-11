cmake_minimum_required(VERSION 3.10)
project(tp1)

set(CMAKE_CXX_STANDARD 11)

add_executable(tp1 main.cpp FamilyTree.cpp FamilyMember.cpp)

target_include_directories(tp1 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
