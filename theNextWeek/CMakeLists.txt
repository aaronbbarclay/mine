cmake_minimum_required (VERSION 2.6)
project (theNextWeek)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(/usr/local/include/opencv4/)
include_directories(/Users/aaronb/Dev/mine/theNextWeek/common/)

find_package(OpenCV REQUIRED)

add_executable(theNextWeek
        src/main.cc

        )

target_link_libraries(theNextWeek ${OpenCV_LIBS})