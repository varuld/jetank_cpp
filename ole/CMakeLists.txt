cmake_minimum_required(VERSION 3.10)
project(SerialTest)


add_executable(stest src/main.cpp src/SCS15.cpp)
target_include_directories(stest PUBLIC src)
