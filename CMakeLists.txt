cmake_minimum_required(VERSION 3.17)
project(coroutine_state_machine)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-fcoroutines)
add_definitions(-fno-exceptions)
add_definitions(-fexceptions)

add_executable(coroutine_state_machine main.cpp
                                    coroutine_resumable.hpp
                                    generator.hpp
                                    states.hpp)