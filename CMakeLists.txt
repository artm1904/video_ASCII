cmake_minimum_required(VERSION 3.10)
project(video_ASCII VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/contrib)

include(cmake/cpm.cmake)


find_package(OpenCV COMPONENTS core imgproc highgui videoio)


if(NOT OpenCV_FOUND)
    message(STATUS "OpenCV not found in system. Fetching and building from source with CPM...")

    CPMAddPackage(
        NAME opencv
        GITHUB_REPOSITORY opencv/opencv
        GIT_TAG 4.12.0
        VERSION 4.12.0 #if in repo tag is like v8.0.7 the GIT_TAG is not nesessarely
        SOURCE_DIR ${LIB_DIR}/opencv
    )

endif()

if(NOT TARGET OpenCV::core AND TARGET opencv_core)
    message(STATUS "Creating ALIAS targets for locally built OpenCV.")
    add_library(OpenCV::core ALIAS opencv_core)
    add_library(OpenCV::imgproc ALIAS opencv_imgproc)
    add_library(OpenCV::highgui ALIAS opencv_highgui)
    add_library(OpenCV::videoio ALIAS opencv_videoio)
endif()


# Устанавливаем опции компилятора для нашего проекта
set(PROJECT_COMPILE_OPTIONS)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    list(APPEND PROJECT_COMPILE_OPTIONS -Wall -Wextra -pedantic)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    list(APPEND PROJECT_COMPILE_OPTIONS -O3)
endif()

add_subdirectory(video_converter)
