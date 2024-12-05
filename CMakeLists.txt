cmake_minimum_required(VERSION 3.10.0)
project(ascii_webcam_stream VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(ascii_webc src/main.cpp src/image_processing.hpp src/image_processing.cpp)

target_link_libraries(ascii_webc ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
