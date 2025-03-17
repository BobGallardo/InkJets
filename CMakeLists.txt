cmake_minimum_required(VERSION 3.10)
project(InkJets)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ensure we use the correct compiler
set(CMAKE_C_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

# Include directories
include_directories(include)

# Define source files
set(SRC_FILES
    src/main.cpp
    src/adsb_parser.cpp
    src/display.cpp
    src/utils.cpp
)

# Find required packages
find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Threads REQUIRED)

# Include Boost directories
include_directories(${Boost_INCLUDE_DIRS})

# Add executable target
add_executable(InkJets ${SRC_FILES})

# Link necessary libraries
target_link_libraries(InkJets
    ${Boost_LIBRARIES}  # Boost system & threading
    Threads::Threads    # Standard threading support
    rtlsdr              # RTL-SDR library for ADS-B
    usb-1.0             # USB library for SDR
    sqlite3             # SQLite support (if needed for future features)
    ncurses             # Ncurses for terminal UI
)

# Crow library setup (Download if missing)
set(CROW_DIR "${CMAKE_SOURCE_DIR}/include/crow")
if(NOT EXISTS "${CROW_DIR}/crow_all.h")
    message(STATUS "Downloading Crow HTTP library...")
    file(DOWNLOAD
        "https://github.com/CrowCpp/Crow/releases/download/v1.2.0/crow_all.h"
        "${CROW_DIR}/crow.h"
        SHOW_PROGRESS
    )
endif()
