cmake_minimum_required(VERSION 3.2.0)
project(model)
set(SOURCE test.cpp)
add_library(model STATIC ${SOURCE})
