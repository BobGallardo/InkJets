cmake_minimum_required(VERSION 3.10)
project(InkJets)

set(CMAKE_C_COMPILER "/usr/bin/g++.exe")
set(CMAKE_CXX_COMPILER "/usr/bin/g++.exe")

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(InkJets src/main.cpp)
