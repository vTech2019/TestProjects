cmake_minimum_required (VERSION 3.0)
project(FcBMP C)

add_library (${PROJECT_NAME} STATIC "FcBMP.c" "FcBMP.h")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")