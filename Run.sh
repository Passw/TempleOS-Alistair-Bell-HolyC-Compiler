#!/bin/bash
cmake -BBuild
cd Build && make
cd ../