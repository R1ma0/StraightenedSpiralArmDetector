cmake_minimum_required(VERSION 3.2.0)

project(detectorator)
set(SOURCE adaptive_zhang_suen.cpp
           detectorator.cpp
           utils.cpp
           zhang_suen.cpp)
add_library(detectorator STATIC ${SOURCE})
