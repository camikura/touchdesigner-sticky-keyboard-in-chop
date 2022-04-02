cmake_minimum_required(VERSION 3.2)
project(StickyKeyboardInCHOP)

include_directories(include)

add_library(StickyKeyboardInCHOP MODULE src/main.cc src/param.cc src/keystate.cc)

if(MSVC)
  target_compile_options(StickyKeyboardInCHOP PUBLIC "/std:c++latest")
endif()
