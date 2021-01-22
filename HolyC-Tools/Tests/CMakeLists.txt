project(HolyC-Tests)

include_directories(../)

function(HolyC_Add_Test_Binary source binary)
    add_executable(${binary} ${source})
    message(STATUS "Adding test ${binary}")
    target_link_libraries(${binary} PUBLIC Core-Backend)
    add_test(NAME ${binary} COMMAND ${binary})
endfunction(HolyC_Add_Test_Binary)

HolyC_Add_Test_Binary(Tests.c Test-Tests)
HolyC_Add_Test_Binary(Tokens.c Test-Tokens)
HolyC_Add_Test_Binary(Hashing.c Test-Hashing)
HolyC_Add_Test_Binary(Parsing.c Test-Parsing)
