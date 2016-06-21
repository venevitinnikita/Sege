cmake_minimum_required(VERSION 3.5)
project(Sege)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/core/event/EventBus.hpp src/numbers.hpp src/core/module.hpp src/core/module.cpp)
add_executable(Sege ${SOURCE_FILES})