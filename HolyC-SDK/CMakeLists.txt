project(HolyC-SDK)
include_directories(../HolyC-Tools)

set(BASE_LIBRARY_SOURCES
    # Sources common to all architectures and os's
)

if (${PROJECT_TARGET_ARCHITECTURE} STREQUAL "amd64")
    if (UNIX)
        set(BASE_LIBRARY_SOURCES
            ${BASE_LIBRARY_SOURCES}
            "Amd64/Linux/Puts.s")
    endif(UNIX)
    set(BASE_LIBRARY_SOURCES ${BASE_LIBRARY_SOURCES} Amd64/Defs.s Amd64/String.s)
endif(${PROJECT_TARGET_ARCHITECTURE} STREQUAL "amd64")

add_library(HolyC-SDK-BaseLibrary ${BASE_LIBRARY_SOURCES})
target_compile_options(HolyC-SDK-BaseLibrary PUBLIC "-O2")
target_include_directories(HolyC-SDK-BaseLibrary PUBLIC Amd64)
