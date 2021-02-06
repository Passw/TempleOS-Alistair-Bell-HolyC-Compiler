project(HolyC-SDK)
include_directories(../HolyC-Tools)

if (${PROJECT_BUILD_ARCHITECTURE} STREQUAL "x86_64" OR
        ${PROJECT_BUILD_ARCHITECTURE} STREQUAL "amd64") 
    set(HOLYC_SDK_AMD64_SOURCES
        Amd64/Defs.s
        Amd64/String.s
        Amd64/Linux/Puts.s
    )
    add_library(HolyC-SDK_Amd64 SHARED ${HOLYC_SDK_AMD64_SOURCES})
    target_include_directories(HolyC-SDK_Amd64 PUBLIC Amd64)
endif()
