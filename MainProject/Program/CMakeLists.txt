
cmake_minimum_required (VERSION 3.13)

project (GraphicsTest VERSION 0.0.1 DESCRIPTION "alpha")
include(GNUInstallDirs)

include_directories(../Library)


set(RuntimeOutputDir ${CMAKE_BINARY_DIR}/out)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${RuntimeOutputDir})
set(-DCMAKE_GENERATOR_PLATFORM x64)
set(lib_targets
    TrueTypeLibrary
    ThreadLibrary
    ${PLATFORM_COMPAT_LIBRARIES}
)
set(PUBLIC_OBJECTS "")
set(PUBLIC_HEADERS "")

foreach(target ${lib_targets})
    list(APPEND PUBLIC_OBJECTS $<TARGET_OBJECTS:${target}>)
    message("Adding public object(s) ${target} to target GraphicsTest")
    get_target_property(TARGETS_PUBLIC_HEADERS ${target} PUBLIC_HEADER)
    if (EXISTS "${TARGETS_PUBLIC_HEADERS}")
        list(APPEND PUBLIC_HEADERS "${TARGETS_PUBLIC_HEADERS}")
        message("Adding public header(s) ${TARGETS_PUBLIC_HEADERS} to target GraphicsTest")
    endif()
endforeach()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src")
foreach(FILE ${SRC_FILES}) 
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")
    if ("${FILE}" MATCHES ".*\\.c")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()
    source_group("${GROUP}" FILES "${FILE}")
endforeach()



find_package(Git)
if(NOT GIT_FOUND)
    message(FATAL_ERROR "git not found!")
else()
    execute_process(
        COMMAND             ${GIT_EXECUTABLE} clone https://github.com/KhronosGroup/OpenGL-Registry/ --recursive ${${SOURCE_DIR}}
        WORKING_DIRECTORY   ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE     git_result
        OUTPUT_VARIABLE     git_output)
    message("OUTPUT: " ${git_output})
endif()

if (LINUX OR UNIX)
    execute_process(
            COMMAND ${CMD}  apt-get install libxext-dev libx11-dev x11proto-gl-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev
            RESULT_VARIABLE     cmd_result
            OUTPUT_VARIABLE     cmd_output
    )#sudo -S
    message("OUTPUT: " ${cmd_output})
	set(OpenGL_GL_PREFERENCE LEGACY) #GLVND
    set(OPENGL_INCLUDE_DIR "${CMAKE_BINARY_DIR}/OpenGL-Registry/api" "/usr/include/GL" "/usr/include/X11/GL")
    #set(OPENGL_gl_LIBRARY "/usr/lib/GL" "/usr/lib/X11/GL")
    find_package(X11)
    if(NOT X11_FOUND)
        message("ERROR: x11 not found")
    else()
        message("MESSAGE: x11 found")
    endif(NOT X11_FOUND)
endif ()

if (CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -O0  -march=native")
endif (CMAKE_COMPILER_IS_GNUCC)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/BINARY")
file(GLOB_RECURSE SHADER_OPENGL_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.glsl" HEX)

foreach (shader ${SHADER_OPENGL_FILE})
    file(READ ${shader} HEX_SHADER_OPENGL_FILE  HEX)
    string(REGEX MATCHALL "([A-Za-z0-9][A-Za-z0-9])" SEPARATED_HEX_SHADER_OPENGL_FILE "${HEX_SHADER_OPENGL_FILE}")
    list(JOIN SEPARATED_HEX_SHADER_OPENGL_FILE ", 0x" FORMATTED_HEX)
    #message("HEX_CONTENTS: ${SEPARATED_HEX_SHADER_OPENGL_FILE}")
    string(PREPEND FORMATTED_HEX "0x")
    get_filename_component (name ${shader} NAME)
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/src/BINARY/${name}.bin "${FORMATTED_HEX}")
    #message("HEX_CONTENTS: ${FORMATTED_HEX}")
endforeach()

file(GLOB_RECURSE SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
  #${CMAKE_CURRENT_SOURCE_DIR}/../../libs/OpenGL/*.c
  #${CMAKE_CURRENT_SOURCE_DIR}/../../libs/OpenGL/*.h
 )
file(GLOB_RECURSE RESOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.glsl.bin
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.glsl
 )

source_group("Source Files" FILES ${SOURCE_FILES})
source_group("Header Files" FILES ${HEADER_FILES})
source_group("Resource Files" FILES ${RESOURCE_FILES})


add_definitions(-DGL_GLEXT_PROTOTYPES=1)
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
if(OPENGL_FOUND)
    message(STATUS "OPENGL_INCLUDE_DIR:= ${OPENGL_INCLUDE_DIR}")
    message(STATUS "OPENGL_LIBRARY:= ${OPENGL_LIBRARY}")
    message(STATUS "OPENGL_LIBRARIES:= ${OPENGL_LIBRARIES}")
endif(OPENGL_FOUND)

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_executable (${PROJECT_NAME} ${PUBLIC_HEADERS} ${SOURCES})

#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../libs/OpenGL-Registry/api)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/BINARY)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_BINARY_DIR}/OpenGL-Registry/api)

if (LINUX OR UNIX)
    target_link_libraries(${PROJECT_NAME} ${X11_LIBRARIES})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC ${OPENGL_LIBRARIES} TrueTypeLibrary 
									  INTERFACE ThreadLibrary)
									  
message(LINK_LIBRARIES : ${LINK_LIBRARIES} )
message(CMAKE_C_FLAGS: ${CMAKE_C_FLAGS} )
