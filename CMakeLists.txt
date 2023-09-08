cmake_minimum_required(VERSION 3.2.0)

project(StraightSpiralArmsDetector)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(wxWidgets COMPONENTS net core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_library(utils STATIC src/detectorator/utils.cpp)
add_library(detectorator STATIC src/detectorator/detectorator.cpp)
add_library(zhang_suen STATIC src/detectorator/zhang_suen.cpp)
add_library(adaptive_zhang_suen STATIC src/detectorator/adaptive_zhang_suen.cpp)
add_library(main_window STATIC src/view/appMainWindow.cpp)
add_executable(${PROJECT_NAME} src/app.cpp)

target_link_libraries(
	${PROJECT_NAME}
	detectorator
	zhang_suen 
	adaptive_zhang_suen
	utils
	main_window
	${wxWidgets_LIBRARIES}
	${OpenCV_LIBS} 
)
target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
