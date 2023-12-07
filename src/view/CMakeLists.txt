cmake_minimum_required(VERSION 3.2.0)
project(view)
set(SOURCE app_main_window.cpp
           detectorator_control_panel.cpp
           bitmap_control_panel.cpp
           buffered_bitmap.cpp
           image_rotate_scale_frame.cpp
)
add_library(view STATIC ${SOURCE})
