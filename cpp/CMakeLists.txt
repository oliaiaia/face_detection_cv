cmake_minimum_required(VERSION 3.10)
project(opencv_face_detector)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR "${CMAKE_SOURCE_DIR}")
add_definitions(-DSOURCE_DIR="${SOURCE_DIR}")

# --- Find OpenCV ---
find_package(OpenCV REQUIRED)

# --- Core library (face detection logic) ---
add_library(face_core src/detector.cpp)
target_include_directories(face_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(face_core PRIVATE ${OpenCV_LIBS})

# --- CLI executable ---
add_executable(face_detector src/base.cpp)
target_include_directories(face_detector PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(face_detector PRIVATE face_core ${OpenCV_LIBS})

# =======================
# ==== Testing setup ====
# =======================
include(CTest)
enable_testing()

# --- Download GoogleTest ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# --- Pass dataset/cascade/results paths to tests ---
add_compile_definitions(
  DATASET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/dataset"
  CASCADE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/teacher_dataset/haarcascade_frontalface_default.xml"
  RESULTS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/results"
  BUILD_BIN_DIR="${CMAKE_CURRENT_BINARY_DIR}"
)

# --- Test executable ---
add_executable(test_detector tests/test_detector.cpp)
target_include_directories(test_detector PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(test_detector PRIVATE face_core GTest::gtest_main ${OpenCV_LIBS})

# --- Automatic test discovery ---
include(GoogleTest)
gtest_discover_tests(test_detector)
