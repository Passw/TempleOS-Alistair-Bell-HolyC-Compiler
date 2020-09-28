# /bin/bash

printf "Calling normally\n"
./Compiler Tests/Main.IC

printf "\nCalling with invalid file\n"
./Compiler Tests/Main.I

printf "\nCalling with buffer over-limit\n"
./Compiler Tests/BufferLimit.bin
