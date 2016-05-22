cmake_minimum_required(VERSION 3.5)
project(arm11_39)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES


        src/emulate.c
        src/decodeAndExecute.c
        src/branch.c
        src/dataTransfer.c
        src/decodeAndExecute.c
        src/dataTransfer.c
        src/branch.c
        src/decodeAndExecute.h
        src/dataTransfer.h
        src/branch.h
        src/emulate.h src/checkCond.h src/checkCond.c src/printState.h src/printState.c src/iMultiply.h src/iMultiply.c src/dataProcess.h src/dataProcess.c src/binaryShift.h src/binaryShift.c)

add_executable(arm11_39 ${SOURCE_FILES})