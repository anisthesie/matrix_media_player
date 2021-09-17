cmake_minimum_required(VERSION 3.20)
project(matrix_media_player)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(matrix_video_player)

add_executable(matrix_media_player
        matrix_video_player/converter-types.h
        matrix_video_player/converter.cpp
        matrix_video_player/converter.h
        matrix_video_player/input_parser.cpp
        matrix_video_player/input_parser.h
        matrix_video_player/main.cc
        matrix_video_player/screenshot.cc
        matrix_video_player/screenshot.h
        matrix_video_player/video_player.cpp
        matrix_video_player/video_player.h)
