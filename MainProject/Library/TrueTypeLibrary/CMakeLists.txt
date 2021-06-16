cmake_minimum_required (VERSION 3.13)

project(TrueTypeLibrary VERSION 0.0.1 DESCRIPTION "TrueType reader")
include(GNUInstallDirs)


add_library(${PROJECT_NAME} STATIC  
	"src/TrueTypeLibrary.h" 
	"src/TrueTypeLibrary.c"
	"src/TrueTypeSize.h" 
	"src/TrueTypeSize.c" 
	"src/TrueTypeFile.h" 
	"src/TrueTypeCmap.h"
	"src/TrueTypeCmap.c"
	"src/TrueTypeMath.h" 
	"src/TrueTypeHead.c"
	"src/TrueTypeHead.h"
	"src/TrueTypeGlyph.h" 
	"src/TrueTypeGlyph.c" 
	"src/TrueTypeMaxp.c" 
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
	"src/TrueTypeTables.h" )
	
	
set_target_properties(${PROJECT_NAME} PROPERTIES
	VERSION ${PROJECT_VERSION}
    OUTPUT_NAME ${PROJECT_NAME}
    FRAMEWORK TRUE
    PUBLIC_HEADER "${PROJECT_SOURCE_DIR}/src/TrueTypeLibrary.h"
    VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    SOVERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)
if(MSVC)
target_compile_options(${PROJECT_NAME} PRIVATE  /arch:AVX /Wall /guard:cf /Qvec-report:2  /Zf /GS /MP /sdl /Zc:preprocessor)
else()
target_compile_options(${PROJECT_NAME} PRIVATE  -march=native -Wall -pedantic -Wextra)
endif()
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
message(INFO "${CMAKE_CURRENT_SOURCE_DIR}")
install(
    TARGETS ${PROJECT_NAME}
    EXPORT "${TARGETS_EXPORT_NAME}"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
	PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_FULL_INCLUDEDIR}"
)

