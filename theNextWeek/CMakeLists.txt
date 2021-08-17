cmake_minimum_required (VERSION 2.6)
project (theNextWeek)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)

if (LINUX)
    MESSAGE("LINUX BUILD CONFIG")
    set(OPENCV_BASE /usr/local/include/)
    set(GIT_BASE /root/)
else()
    MESSAGE("APPLE BUILD CONFIG")
    set(OPENCV_BASE /usr/include/)
    set(GIT_BASE /Users/aaronb/Dev/)
endif()

include_directories(${OPENCV_BASE}/opencv4/)
include_directories(${GIT_BASE}/mine/theNextWeek/common/)

find_package(OpenCV REQUIRED)

add_executable(theNextWeek
        src/main.cc

        )

target_link_libraries(theNextWeek ${OpenCV_LIBS})