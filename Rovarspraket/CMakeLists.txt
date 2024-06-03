cmake_minimum_required(VERSION 3.25)
project(Rovarspraket)

set(CMAKE_CXX_STANDARD 17)

add_executable(Rovarspraket main.cpp Model.cpp Model.h Translator.cpp Translator.h FileProcessor.cpp FileProcessor.h)
