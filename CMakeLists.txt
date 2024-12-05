cmake_minimum_required(VERSION 3.10.0)
project(openCV_test VERSION 0.1.0 LANGUAGES C CXX)

find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE_DIRS})


add_executable(openCV_test main.cpp)

target_link_libraries(openCV_test ${OpenCV_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
