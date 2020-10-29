#!/bin/bash
cmake -BBuild
cd Build && make
cd ../

./Build/Improved-C/Compiler/Improved-C-Compiler