# set cmake minimum version
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(CMakeTest VERSION 1.0)

#include and link source folder
include_directories(Jetank)
link_directories(Jetank)

# add the executable
add_executable(demo_program demo.cpp)

# add sort library

# link the library
target_link_libraries(demo_program)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# make release the default build
if(NOT CMAKE_BUILD_TYPE)
	  set(CMAKE_BUILD_TYPE Release)
	    message(STATUS "Build type not specified: Use Release by default")
	endif()

	set(CMAKE_CXX_FLAGS "-Wall -Wextra")
	set(CMAKE_CXX_FLAGS_DEBUG "-g")
	set(CMAKE_CXX_FLAGS_RELEASE "-O3")

	message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
