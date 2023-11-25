cmake_minimum_required(VERSION 3.2.0)
project(controller)
set(SOURCE app_main_window_controller.cpp
           i_controller.hpp)
add_library(model STATIC ${SOURCE})
