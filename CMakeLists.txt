cmake_minimum_required(VERSION 3.2.0)

project(StraightSpiralArmsDetector)

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/..)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(wxWidgets COMPONENTS net core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(
    ${PROJECT_NAME} 
    src/app.cpp 
    src/view/app_main_window.cpp
    src/view/detectorator_control_panel.cpp
    src/view/bitmap_control_panel.cpp
    src/view/buffered_bitmap.cpp
    src/model/processed_image.cpp
    src/model/converters.cpp
    src/model/detectorator/adaptive_zhang_suen.cpp
    src/model/detectorator/utils.cpp
    src/model/detectorator/zhang_suen.cpp
)

target_link_libraries(
	${PROJECT_NAME}
	${wxWidgets_LIBRARIES}
	${OpenCV_LIBS} 
)
target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})
