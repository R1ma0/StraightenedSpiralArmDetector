cmake_minimum_required(VERSION 2.8)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
project(DetectoratorOfStringsOfGalaxies)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(detectorator STATIC detectorator.cpp)
add_library(zhang_suen STATIC skeletonization_zhang_suen.cpp)
add_executable(DetectoratorOfStringsOfGalaxies main.cpp)

target_link_libraries(
	DetectoratorOfStringsOfGalaxies 
	${OpenCV_LIBS} 
	zhang_suen 
	detectorator
)
