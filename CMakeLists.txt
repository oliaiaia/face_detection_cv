cmake_minimum_required(VERSION 3.10)
project(opencv_face_detector)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}")
add_definitions(-DSOURCE_DIR="${SOURCE_DIR}")

find_package(OpenCV REQUIRED)

add_executable(face_detector src/base.cpp)
target_include_directories(face_detector PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(face_detector PRIVATE ${OpenCV_LIBS})
