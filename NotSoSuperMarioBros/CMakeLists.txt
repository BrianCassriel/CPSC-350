cmake_minimum_required(VERSION 3.25)
project(NotSoSuperMarioBros)

set(CMAKE_CXX_STANDARD 17)

add_executable(NotSoSuperMarioBros NotSoSuperMarioBros.cpp Logger.cpp Logger.h World.cpp World.h Mario.cpp Mario.h)
