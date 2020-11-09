project(HolyC-Tests)

include_directories(../)

function(HolyC_Add_Test_Binary source binary)
    add_executable(${binary} ${source})
    message(STATUS "Adding test ${binary}")
    target_link_libraries(${binary} PUBLIC Core-Backend)
endfunction(HolyC_Add_Test_Binary)

function(HolyC_Add_Test_Assemby_Amd64 source binary)
    add_executable(${binary} ${source})
    target_compile_options(${binary} PUBLIC "--64")
endfunction(HolyC_Add_Test_Assemby_Amd64 source binary)

if (${PROJECT_TARGET_ARCHITECTURE} STREQUAL "amd64" AND UNIX)
    HolyC_Add_Test_Assemby_Amd64(Amd64-Linux/HelloWorld.s Test-HelloWorld)
endif(${PROJECT_TARGET_ARCHITECTURE} STREQUAL "amd64" AND UNIX)

HolyC_Add_Test_Binary(Tests.c Test-Tests)
HolyC_Add_Test_Binary(Tokens.c Test-Tokens)
HolyC_Add_Test_Binary(Hashing.c Test-Hashing)
