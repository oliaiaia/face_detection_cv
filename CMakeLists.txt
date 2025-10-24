cmake_minimum_required(VERSION 3.10)
project(face_detection_cv)

# --- OpenCV ---
find_package(OpenCV REQUIRED)

# --- Main library with face detection logic ---
add_library(face_core src/detector.cpp)
target_include_directories(face_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(face_core PRIVATE ${OpenCV_LIBS})

# --- CLI executable ---
add_executable(face_detect src/base.cpp)
target_link_libraries(face_detect PRIVATE face_core ${OpenCV_LIBS})

# --- Testing ---
include(CTest)
enable_testing()

# --- Include GoogleTest ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Test binary ---
add_executable(test_detector tests/test_detector.cpp)
target_link_libraries(test_detector PRIVATE face_core GTest::gtest_main ${OpenCV_LIBS})

# --- Automatic test discovery ---
include(GoogleTest)
gtest_discover_tests(test_detector)
