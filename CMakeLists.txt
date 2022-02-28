# checks CMake version and sets to the available one.
cmake_minimum_required(VERSION 3.7...3.22)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()


# project description with a some additional information
project(CTAT VERSION 1.0
             DESCRIPTION "Crypto Tracking and Trading"
             LANGUAGES CXX)   



# default CXX Flags             
set(CMAKE_CXX_STANDARD 17 CACHE STRING "C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# some additional variables defined 
set(TICKER "ticker")


#include dirs
include_directories(
    ${TICKER}/include/
)


# adding subdirectory which includes CMakeLists.txt for that particular dir
add_subdirectory(ticker)
add_subdirectory(pybind_ticker)
