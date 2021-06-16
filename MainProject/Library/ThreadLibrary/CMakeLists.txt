

cmake_minimum_required (VERSION 3.13)
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})

set(PROJECT_SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}/ThreadLibrary.h")
if(WIN32)
    list(APPEND PROJECT_SOURCES  
    "${CMAKE_CURRENT_SOURCE_DIR}/WINAPI_Thread.h" 
    "${CMAKE_CURRENT_SOURCE_DIR}/WINAPI_Mutex.h" 
    )
endif()
add_library(${PROJECT_NAME} INTERFACE)
target_sources(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCES}) 
target_include_directories(${PROJECT_NAME} INTERFACE
  "${CMAKE_CURRENT_SOURCE_DIR}"
)