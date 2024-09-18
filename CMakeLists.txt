cmake_minimum_required(VERSION 3.27)
project(CO2203_Group03_Assignment03)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CO2203_Group03_Assignment03
        Calendar.cpp
        Calendar.h
        Event.cpp
        Event.h
        main.cpp
        Utils.h)
