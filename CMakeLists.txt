cmake_minimum_required(VERSION 3.26)
project(second_paradigms)

set(CMAKE_CXX_STANDARD 17)

add_executable(second_paradigms main.cpp
        LinkedList.h
        LinkedList.cpp
        Stack.cpp
        Stack.h
        fileWriterReader.cpp
        fileWriterReader.h
        DynamicLib.cpp
        DynamicLib.h
        CommandProcessor.cpp
        CommandProcessor.h
)
