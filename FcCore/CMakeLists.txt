
cmake_minimum_required(VERSION 3.16)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)
set(SOFT_VERSION ${VERSION_MAJOR}. ${VERSION_MINOR}. ${VERSION_PATCH})

project("FcCore")

# DEBUG|RELEASE|RELWITHDEBINFO|MINSIZEREL
#set( CMAKE_BUILD_TYPE RELEASE )

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/common/config.h.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h"
        @ONLY)

file(GLOB_RECURSE FcGL "src/FcGL/*")
file(GLOB_RECURSE FcImage "src/FcImage/*")
file(GLOB_RECURSE FcUnix "src/UNIX/*")
file(GLOB_RECURSE FcWINAPI "src/WINAPI/*")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${RuntimeOutputDir})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${RuntimeOutputDir})

set(Sources
        ${FcGL}
        ${FcImage}
        ${FcUnix}
        ${FcWINAPI}
        "../TrueTypeLibrary/src/FcTrueTypeGL.h"
        "../TrueTypeLibrary/src/FcTrueTypeGL.c"
        "src/include/FcFilesystem.h"
        "src/include/FcThread.h"
        "src/include/FcWindow.h"
        "src/include/FcMath.h"
        "src/include/FcCore.h"
        "src/include/FcPNG.h"
        "src/include/FcZlib.h"
        "src/Algorithm/Fc_ProducerConsumer.h"
        "src/Algorithm/Fc_ProducerConsumer.c"
        src/FcGL/FcGLX.h
        src/FcGL/FcDebug.c
        src/Algorithm/FcSort.h
        src/Algorithm/FcSSE2.h
        src/Algorithm/FcSortStatic.h
        src/include/FcError.h
        src/FcError.c
        src/FcError.c src/FcStatic.c src/FcGL/FcEGL.h)

set(OPENGL_DIR ${CMAKE_CURRENT_BINARY_DIR}/OpenGL_Headers)
if (NOT EXISTS "${OPENGL_DIR}")
    make_directory("${OPENGL_DIR}")
endif ()
if (NOT EXISTS "${OPENGL_DIR}/GL")
    make_directory("${OPENGL_DIR}/GL")
endif ()
if (NOT EXISTS "${OPENGL_DIR}/KHR")
    make_directory("${OPENGL_DIR}/KHR")
endif ()

set(OpenGL_Headers
        "${OPENGL_DIR}/KHR/khrplatform.h"
        "${OPENGL_DIR}/GL/glcorearb.h"
        )
set(OpenGL_Headers_URL
        "http://www.khronos.org/registry/EGL/api/KHR/khrplatform.h"
        "http://www.khronos.org/registry/OpenGL/api/GL/glcorearb.h"
        )

set(file_counter 1)

if (WIN32)
    list(APPEND OpenGL_Headers "${OPENGL_DIR}/GL/wglext.h")
    list(APPEND OpenGL_Headers "${OPENGL_DIR}/GL/wgl.h")
    list(APPEND OpenGL_Headers_URL "http://www.khronos.org/registry/OpenGL/api/GL/wglext.h")
    list(APPEND OpenGL_Headers_URL "http://www.khronos.org/registry/OpenGL/api/GL/wgl.h")
    set(file_counter "3")
elseif (LINUX OR UNIX)
    list(APPEND OpenGL_Headers "${OPENGL_DIR}/GL/glxext.h")
    list(APPEND OpenGL_Headers_URL "http://www.khronos.org/registry/OpenGL/api/GL/glxext.h")
    set(file_counter "2")
endif ()

foreach (i RANGE ${file_counter})
    list(GET OpenGL_Headers ${i} header)
    list(GET OpenGL_Headers_URL ${i} header_url)
    message(STATUS "OPENGL URL: ${header_url} HEADER: ${header} ")
    if (NOT EXISTS ${header})
        message("Downloading files...")
        file(DOWNLOAD ${header_url} ${header}
                SHOW_PROGRESS
                STATUS DOWNLOAD_RESULT
                LOG DOWNLOAD_LOG)
        list(GET DOWNLOAD_RESULT 0 DOWNLOAD_RESULT_CODE)
        if (NOT DOWNLOAD_RESULT_CODE EQUAL 0)
            message(FATAL_ERROR "Failed downloading! Error: ${DOWNLOAD_RESULT_CODE}. ${DOWNLOAD_LOG}")
        endif ()
    endif ()
endforeach ()

if (LINUX OR UNIX)
    add_definitions(-DGL_GLEXT_PROTOTYPES=1)
    execute_process(
            COMMAND ${CMD} apt-get install libxext-dev libx11-dev x11proto-gl-dev libglu1-mesa-dev freeglut3-dev mesa-common-dev
            RESULT_VARIABLE cmd_result
            OUTPUT_VARIABLE cmd_output
    )#sudo -S
    message("OUTPUT: " ${cmd_output})
    set(OpenGL_GL_PREFERENCE LEGACY) #GLVND
    set(OPENGL_INCLUDE_DIR ${OpenGL_Headers})
    #set(OPENGL_gl_LIBRARY "/usr/lib/GL" "/usr/lib/X11/GL")
    find_package(X11)
    if (NOT X11_FOUND)
        message("ERROR: x11 not found")
    else ()
        message("MESSAGE: x11 found")
    endif (NOT X11_FOUND)
endif ()
if (WIN32)
    #add_compile_definitions(NOGDI)
endif ()

find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
if (OPENGL_FOUND)
    message(STATUS "OPENGL_INCLUDE_DIR:= ${OPENGL_INCLUDE_DIR}")
    message(STATUS "OPENGL_LIBRARY:= ${OPENGL_LIBRARY}")
    message(STATUS "OPENGL_LIBRARIES:= ${OPENGL_LIBRARIES}")
endif (OPENGL_FOUND)

add_library(FcCore STATIC ${Sources})

message(${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/OpenGL-Registry/api)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include)
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENGL_DIR})


if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE "opengl32.lib")
elseif (LINUX OR UNIX)
    message(STATUS "LINUX:= ${OPENGL_LIBRARIES} ${X11_LIBRARIES}")
    #target_link_libraries(${PROJECT_NAME} PRIVATE "libGL.so" "X11.so")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_DL_LIBS} ${OPENGL_LIBRARIES} ${X11_LIBRARIES} "libpthread.so")
endif ()
