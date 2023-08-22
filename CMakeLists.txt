cmake_minimum_required(VERSION 3.2.0)
project(DetectoratorOfStringsOfGalaxies)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

add_library(common_functions STATIC src/detectorator/common_functions.cpp)
add_library(detectorator STATIC src/detectorator/detectorator.cpp)
add_library(zhang_suen STATIC src/detectorator/zhang_suen.cpp)
add_executable(DSG src/app.cpp)

target_link_libraries(
	DSG
	detectorator
	zhang_suen 
	common_functions
	${wxWidgets_LIBRARIES}
	${OpenCV_LIBS} 
)
target_include_directories(DSG PRIVATE ${wxWidgets_INCLUDE_DIRS})
