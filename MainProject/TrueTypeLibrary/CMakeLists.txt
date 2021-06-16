cmake_minimum_required (VERSION 3.13)


get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} VERSION 0.0.1 DESCRIPTION "TrueType reader")
include(GNUInstallDirs)


add_library(${PROJECT_NAME} STATIC  
	"TrueTypeReader.h" 
	"TrueTypeReader.c"
	"TrueTypeSize.h" 
	"TrueTypeSize.c" 
	"TrueTypeFile.h" 
	"TrueTypeCmap.h"
	"TrueTypeCmap.c"
	"TrueTypeMath.h" 
	"TrueTypeHead.c"
	"TrueTypeHead.h"
	"TrueTypeGlyph.h" 
	"TrueTypeGlyph.c" 
	"TrueTypeMaxp.c" 
	"TrueTypeMaxp.h" 
	"TrueTypeHhea.c" 
	"TrueTypeHhea.h" 
	"TrueTypeName.h" 
	"TrueTypeLoca.h" 
	"TrueTypeHmtx.c"
	"TrueTypeHmtx.h"
	"TrueTypeMalloc.h"
	"TrueTypeMalloc.c" 
	"TrueTypeTables.c" 
	"TrueTypeTables.h" 
	"TrueTypeError.h" 
	"TrueTypeTables.h" )
	
	
set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
    OUTPUT_NAME ${PROJECT_NAME}
    FRAMEWORK TRUE
    PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/TrueTypeReader.h"
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
if(MSVC)
target_compile_options(${PROJECT_NAME} PUBLIC  /arch:AVX /Wall /guard:cf /Qvec-report:2  /Zf /GS /MP /sdl /Zc:preprocessor)
else()
target_compile_options(${PROJECT_NAME} PUBLIC  -march=native -Wall -pedantic -Wextra)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

install(
    TARGETS ${PROJECT_NAME}
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
	PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
)

