cmake_minimum_required(VERSION 3.2.0)
project(controller)
set(SOURCE i_controller.hpp
           app_main_window_controller.cpp
           bitmap_control_panel_controller.cpp
           detectorator_control_panel_controller.cpp
           )
add_library(model STATIC ${SOURCE})
