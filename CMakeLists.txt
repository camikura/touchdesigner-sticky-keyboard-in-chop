cmake_minimum_required(VERSION 3.2)
project(StickyKeyboardInCHOP)

include_directories(include)

add_library(StickyKeyboardInCHOP MODULE src/main.cpp src/param.cpp)
