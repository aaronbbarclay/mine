cmake_minimum_required (VERSION 2.6)
project (RayOne)

set (CMAKE_CXX_STANDARD 11)

#SET("OpenCV_DIR" "")
include_directories(/usr/local/include/opencv4/)
find_package(OpenCV REQUIRED)

add_executable(raymondo src/exrWriteTest.cpp)

target_link_libraries(raymondo ${OpenCV_LIBS})