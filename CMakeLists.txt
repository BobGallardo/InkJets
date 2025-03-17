cmake_minimum_required(VERSION 3.10)
project(InkJets)

# Set the C++ compiler explicitly
set(CMAKE_C_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Specify the C++ standard (use C++20 for best compatibility)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

# Define source files
set(SRC_FILES
    src/main.cpp
    src/adsb_parser.cpp
    src/display.cpp
    src/utils.cpp
)

# Add executable
add_executable(InkJets ${SRC_FILES})

# Link required libraries
target_link_libraries(InkJets rtlsdr usb-1.0 sqlite3 pthread ncurses)

