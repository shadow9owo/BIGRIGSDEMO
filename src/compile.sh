#!/bin/bash
set -e

g++ -Wnarrowing -std=c++17 -I/usr/include \
    *.cpp -o nesjam \
    -lnoise -lraylib -lm -lpthread -ljsoncpp

mv ./nesjam ../
cd ../
./nesjam
