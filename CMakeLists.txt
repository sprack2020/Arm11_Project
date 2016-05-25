cmake_minimum_required(VERSION 3.5)
project(arm11_39)

set(CMAKE_C_FLAGS "-Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic")

set(SOURCE_FILES


        src/emulate.c
        src/emulate.h
        src/decodeAndExecute.c
        src/decodeAndExecute.h
        src/branch.c
        src/branch.h
        src/dataTransfer.c
        src/dataTransfer.h
        src/checkCond.h
        src/checkCond.c
        src/printState.h
        src/printState.c
        src/iMultiply.h
        src/iMultiply.c
        src/dataProcess.h
        src/dataProcess.c
        src/getOperand2.h
        src/getOperand2.c
        src/updateCPSR.h
        src/updateCPSR.c
        src/util.c
        src/util.h
        )

add_executable(arm11_39 ${SOURCE_FILES})