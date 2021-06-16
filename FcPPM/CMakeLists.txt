
cmake_minimum_required (VERSION 3.0.2)
project(FcPPM C)
add_library (${PROJECT_NAME} STATIC "FcPPM.c" "FcPPM.h")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_C_FLAGS: ${CMAKE_C_FLAGS}" )
