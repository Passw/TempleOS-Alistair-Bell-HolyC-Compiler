project(HolyC-SDK)


set(BASE_LIBRARY_SOURCES
    # Sources common to all architectures and os's
)

if (${PROJECT_TARGET_ARCHITECTURE} STREQUAL "amd64")
    if (UNIX)
        set(BASE_LIBRARY_SOURCES
            ${BASE_LIBRARY_SOURCES}
            "Amd64/Linux/Puts.s")
    endif(UNIX)
    set(BASE_LIBRARY_SOURCES ${BASE_LIBRARY_SOURCES} "Amd64/Defs.s")
endif(${PROJECT_TARGET_ARCHITECTURE} STREQUAL "amd64")

add_compile_options()
add_library(HolyC-SDK-BaseLibrary ${BASE_LIBRARY_SOURCES})
target_compile_options(HolyC-SDK-BaseLibrary PUBLIC "--64")