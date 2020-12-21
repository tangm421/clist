
add_definitions(-DPROJECT_COMPILING)

if(CLIST_DEBUG_ON)
    add_definitions(-DCLIST_DEBUG)
endif()

set(HEADERS
    clist.h)

set(SOURCES
    clist.c)

include_directories(${CLIST_INTERNAL_INCLUDES})

if(COMPILE_STATIC)
    add_library(clist-static STATIC ${HEADERS} ${SOURCES})
    set_target_properties(clist-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
    set_target_properties(clist-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set(CLIST_INSTALLTARGETS clist-static)
else()
    add_library(clist-shared SHARED ${SOURCES} ${HEADERS})
    set_target_properties(clist-shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
    set_target_properties(clist-shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)
    set_target_properties(clist-shared PROPERTIES VERSION ${PACKAGE_VERSION})
    set(CLIST_INSTALLTARGETS clist-shared)
endif()

install(FILES ${PROJECT_BINARY_DIR}/clist/config.h DESTINATION include)
install(FILES ${HEADERS} DESTINATION include)
install(TARGETS ${CLIST_INSTALLTARGETS} DESTINATION ${LIBRARY_INSTALL_DIR})