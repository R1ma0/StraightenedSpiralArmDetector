cmake_minimum_required(VERSION 3.2)

project(StraightSpiralArmsDetector)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_library(utils STATIC lib/utils.cpp)
add_library(detectorator STATIC lib/detectorator.cpp)
add_library(zhang_suen STATIC lib/zhangSuen.cpp)
add_executable(${PROJECT_NAME} test.cpp)

target_link_libraries(
	${PROJECT_NAME} 
	detectorator
	zhang_suen 
	utils
	${OpenCV_LIBS} 
)
