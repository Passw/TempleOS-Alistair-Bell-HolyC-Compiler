project(Improved-C-Tests)

include_directories(../)

function(Improved_C_Add_Test_Binary source binary)
    add_executable(${binary} ${source})
    target_link_libraries(${binary} PUBLIC Improved-C-SDK)
endfunction(Improved_C_Add_Test_Binary)

Improved_C_Add_Test_Binary(Tests.c Test-Tests)
Improved_C_Add_Test_Binary(Tokens.c Test-Tokens)
