cmake_minimum_required(VERSION 3.26)
project(SpanningTheGamut)

set(CMAKE_CXX_STANDARD 17)

add_executable(SpanningTheGamut main.cpp
        FileProcessor.h
        FileProcessor.cpp
        WGraph.h
        WGraph.cpp
        WEdge.h)
