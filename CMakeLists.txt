cmake_minimum_required(VERSION 2.8.12.2)
project(clist)

set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION_TWEAK 1114)
set(PACKAGE_VERSION \"${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}\")

if(NOT MSVC)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/clist/")
endif()

set (_DEFAULT_LIBRARY_INSTALL_DIR lib)
if (EXISTS "${CMAKE_INSTALL_PREFIX}/lib32/" AND CMAKE_SIZEOF_VOID_P EQUAL 4)
	set (_DEFAULT_LIBRARY_INSTALL_DIR lib32)
elseif (EXISTS "${CMAKE_INSTALL_PREFIX}/lib64/" AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	set (_DEFAULT_LIBRARY_INSTALL_DIR lib64)
endif ()

set(LIBRARY_INSTALL_DIR "${_DEFAULT_LIBRARY_INSTALL_DIR}" CACHE PATH "Library installation directory")
if(NOT IS_ABSOLUTE "${LIBRARY_INSTALL_DIR}")
	set(LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/${LIBRARY_INSTALL_DIR}")
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set(COMPILE_STATIC ON CACHE BOOL "Flag indicating if a static library should be built, or a dynamic one")
set(CLIST_DEBUG_ON OFF CACHE BOOL "Flag indicating if enable to print clist debug info")

if(NOT MSVC OR COMPILE_STATIC)
    set(PROJECT_IMPORT "")
    set(PROJECT_EXPORT "")
else()
    set(PROJECT_IMPORT "__declspec(dllimport)")
    set(PROJECT_EXPORT "__declspec(dllexport)")
endif()

if(NOT MSVC)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -Wall -g -ggdb")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3 -Wall")
endif()

set(PROJECT_LIB optimized   "${LIBRARY_INSTALL_DIR}/clist.lib" 
                debug       "${LIBRARY_INSTALL_DIR}/clist_d.lib")

configure_file(
    "${PROJECT_SOURCE_DIR}/clist/config.h.in"
    "${PROJECT_BINARY_DIR}/clist/config.h"
)
add_definitions(-DHAVE_CONFIG_H)

set(CLIST_INTERNAL_INCLUDES "${PROJECT_SOURCE_DIR}/clist" "${PROJECT_BINARY_DIR}/clist")

add_subdirectory(clist)
add_subdirectory(samples)
