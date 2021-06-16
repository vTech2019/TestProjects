cmake_minimum_required(VERSION 3.16)

project(TrueTypeLibrary VERSION 0.0.1 DESCRIPTION "TrueType reader")
set(CMAKE_C_STANDARD 11)
set(SOURCE_FILES
		"src/stdafx.h"
		"src/stdafx.c"
        "src/TrueTypeLibrary.h"
        "src/TrueTypeLibrary.c"
        "src/TrueTypeGL.h"
        "src/TrueTypeGL.c"
        "src/TrueTypeGpos.h"
        "src/TrueTypeGpos.c"
        "src/TrueTypeSize.h"
        "src/TrueTypeSize.c"
        "src/TrueTypeFileRead.h"
        "src/TrueTypeFile.h"
        "src/TrueTypeCmap.h"
        "src/TrueTypeCmap.c"
        "src/TrueTypeMath.h"
        "src/TrueTypeHead.c"
        "src/TrueTypeHead.h"
        "src/TrueTypeGlyph.h"
        "src/TrueTypeGlyph.c"
        "src/TrueTypeMaxp.h"
        "src/TrueTypeHhea.c"
        "src/TrueTypeHhea.h"
        "src/TrueTypeName.h"
        "src/TrueTypeLoca.h"
        "src/TrueTypeHmtx.c"
        "src/TrueTypeHmtx.h"
        "src/TrueTypeMalloc.h"
        "src/TrueTypeMalloc.c"
        "src/TrueTypeTables.c"
        "src/TrueTypeTables.h"
        "src/TrueTypeError.h"
        "src/TrueTypeTables.h"
        "src/TrueTypeSDF.h"
        "src/TrueTypeAlgo.h"
        )

#if (MSVC)   
#    set (CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} /Yustdafx.h /FIstdafx.h")
#    set (CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} /Yustdafx.h /FIstdafx.h")
#    set_source_files_properties(
#        src/stdafx.c
#        PROPERTIES
#        COMPILE_FLAGS "/Ycstdafx.h"
#    )    
#    list(APPEND ${SOURCE_FILES} src/stdafx.c)
#    message(${SOURCE_FILES}) 
#endif (MSVC)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})


set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        OUTPUT_NAME ${PROJECT_NAME}
        FRAMEWORK TRUE
        PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/src/TrueTypeLibrary.h"
        VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE 
    /favor:ATOM
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

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
install(
        TARGETS ${PROJECT_NAME}
        EXPORT "${TARGETS_EXPORT_NAME}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
)
message("ID : ${CMAKE_C_COMPILER_ID}; VERSION : ${CMAKE_C_COMPILER_VERSION}")
set(LINK_MATH "GNU" "Clang" )

if(CMAKE_C_COMPILER_ID IN_LIST LINK_MATH)
    target_link_libraries(${PROJECT_NAME} m)
endif()




