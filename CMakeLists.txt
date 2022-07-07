cmake_minimum_required(VERSION 3.20)
project(SmartPointers)

set(CMAKE_CXX_STANDARD 17)
add_executable(SmartPointers main.cpp unique.h my_int.h Deleters/default_deleter.h)
