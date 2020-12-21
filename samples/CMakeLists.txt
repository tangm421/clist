
set(INS_BINDIR \"${EXECUTABLE_OUTPUT_PATH}\")
configure_file(
    "${PROJECT_SOURCE_DIR}/samples/mydefines.h.in"
    "${PROJECT_BINARY_DIR}/samples/mydefines.h"
)
add_definitions(-D_BINDIR=\"${EXECUTABLE_OUTPUT_PATH}\")

set(CLIST_INTERNAL_INCLUDES "${CLIST_INTERNAL_INCLUDES}" "${PROJECT_SOURCE_DIR}/samples" "${PROJECT_BINARY_DIR}/samples")

include_directories(${CLIST_INTERNAL_INCLUDES})

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(SAMPLES_INSTALLTARGETS test-c)
add_executable(${SAMPLES_INSTALLTARGETS} test.c)
if(COMPILE_STATIC)
    target_link_libraries(${SAMPLES_INSTALLTARGETS} clist-static)
else()
    target_link_libraries(${SAMPLES_INSTALLTARGETS} clist-shared)
endif()

install(TARGETS ${SAMPLES_INSTALLTARGETS} DESTINATION bin)

