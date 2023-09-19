cmake_minimum_required(VERSION 3.2.0)
project(model)
set(SOURCE buffered_bitmap.cpp)
add_library(model STATIC ${SOURCE})
