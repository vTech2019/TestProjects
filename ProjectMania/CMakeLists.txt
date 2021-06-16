
cmake_minimum_required(VERSION 3.8)

project("ProjectMania" C)

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)
#set(CMAKE_GENERATOR_PLATFORM x64)
add_subdirectory("../FcPPM" FcPPM)
add_subdirectory("../FcBMP" FcBMP)
add_subdirectory("../FcCore" FcCore)
add_subdirectory("../TrueTypeLibrary" TrueTypeLibrary)


file(GLOB_RECURSE Source_Launcher "src/Launcher/*.c")
file(GLOB_RECURSE Header_Launcher "src/Launcher/*.h")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders/BINARY")
file(GLOB_RECURSE SHADER_OPENGL_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders/*.glsl" HEX)

foreach (shader ${SHADER_OPENGL_FILE})
    file(READ ${shader} HEX_SHADER_OPENGL_FILE HEX)
    string(REGEX MATCHALL "([A-Za-z0-9][A-Za-z0-9])" SEPARATED_HEX_SHADER_OPENGL_FILE "${HEX_SHADER_OPENGL_FILE}")
    list(JOIN SEPARATED_HEX_SHADER_OPENGL_FILE ", 0x" FORMATTED_HEX)
    #message("HEX_CONTENTS: ${SEPARATED_HEX_SHADER_OPENGL_FILE}")
    string(PREPEND FORMATTED_HEX "0x")
    get_filename_component(name ${shader} NAME)
    file(WRITE ${CMAKE_CURRENT_SOURCE_DIR}/src/Shaders/BINARY/${name}.bin "${FORMATTED_HEX}")
    #message("HEX_CONTENTS: ${FORMATTED_HEX}")
endforeach ()
source_group("Shaders" FILES ${SHADER_OPENGL_FILE})

#find_package(OpenMP REQUIRED)


add_executable(ProjectMania "src/App.c" "src/App.h" "src/main.c" ${Header_Launcher} ${Source_Launcher} ${SHADER_OPENGL_FILE} src/SortTest.c)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /openmp:experimental
            /Wall
            /guard:cf
            /Qvec-report:2
            /GS
            /MP
            /sdl
            /Zc:preprocessor)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -march=native
            #-fopenmp
            -g3
            #-Werror
            #-Wall
            #-Wextra
            #-Wpedantic
            #-Wcast-align
            #-Wcast-qual
            #-Wconversion
            #-Wctor-dtor-privacy
            #-Wenum-compare
            #-Wfloat-equal
            #-Wnon-virtual-dtor
            #-Wold-style-cast
            #-Woverloaded-virtual
            #-Wredundant-decls
            #-Wsign-conversion
            #-Wsign-promo
            )
endif ()
target_link_libraries(${PROJECT_NAME} FcCore TrueTypeLibrary FcBMP FcPPM ${OpenMP_C_LIBRARIES})
