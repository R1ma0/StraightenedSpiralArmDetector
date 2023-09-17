cmake_minimum_required(VERSION 3.2.0)

project(StraightSpiralArmsDetector)

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(wxWidgets COMPONENTS net core base REQUIRED)
include(${wxWidgets_USE_FILE})

include_directories(src/detectorator)
include_directories(src/model)
include_directories(src/view)

add_executable(${PROJECT_NAME} src/app.cpp)

add_subdirectory(src/detectorator)
add_subdirectory(src/model)
add_subdirectory(src/view)

target_link_libraries(
	${PROJECT_NAME}
	${wxWidgets_LIBRARIES}
	${OpenCV_LIBS} 
    detectorator
    model
	view
)
target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
