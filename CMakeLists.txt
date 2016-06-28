cmake_minimum_required(VERSION 3.5)
project(Sege)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/core/event/EventBus.hpp src/numbers.hpp src/core/module.hpp src/core/module.cpp test/core/event/EventBusFixture.cpp)
add_executable(Sege ${SOURCE_FILES})

#Google Test
add_subdirectory(lib/googletest)
include_directories(lib/googletest/include)
target_link_libraries(Sege gtest gtest_main)