project(HolyC-Tests)

include_directories(../)

function(HolyC_Add_Test_Binary source binary)
    add_executable(${binary} ${source})
    target_link_libraries(${binary} PUBLIC Core-Backend)
    message(STATUS "Adding test ${binary}")
endfunction(HolyC_Add_Test_Binary)

function(HolyC_Add_Test_Assemby source binary)
    add_executable(${binary} ${source})
endfunction()

HolyC_Add_Test_Binary(Tests.c Test-Tests)
HolyC_Add_Test_Binary(Tokens.c Test-Tokens)
HolyC_Add_Test_Assemby(Nasm-Assembler.asm Test-Nasm-Assembler)
