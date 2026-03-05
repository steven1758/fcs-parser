cmake_minimum_required(VERSION 3.10)

# Set project name and version
project(FCS_Parser VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
add_executable(fcs_parser main.cpp)  # Replace 'main.cpp' with the actual source files
