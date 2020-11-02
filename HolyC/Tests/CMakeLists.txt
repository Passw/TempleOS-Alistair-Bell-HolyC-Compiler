project(HolyC-Tests)

include_directories(../)

function(HolyC_Add_Test_Binary source binary)
    add_executable(${binary} ${source})
    target_link_libraries(${binary} PUBLIC HolyC-SDK)
    message(STATUS "Adding test ${binary}")
endfunction(HolyC_Add_Test_Binary)

HolyC_Add_Test_Binary(Tests.c Test-Tests)
HolyC_Add_Test_Binary(Tokens.c Test-Tokens)
