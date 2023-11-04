cmake_minimum_required(VERSION 3.2.0)
project(model)
set(SOURCE processed_image.cpp)
add_library(model STATIC ${SOURCE})
