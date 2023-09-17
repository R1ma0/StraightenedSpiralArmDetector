cmake_minimum_required(VERSION 3.2.0)
project(view)
set(SOURCE app_main_window.cpp)
add_library(view STATIC ${SOURCE})
