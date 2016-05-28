cmake_minimum_required(VERSION 3.5)
project(arm11_39)

set(CMAKE_C_FLAGS "-Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic")

set(SOURCE_FILES
        src/decodeAndExecute.c
        src/branch.c
        src/dataTransfer.c
        src/checkCond.c
        src/printState.c
        src/iMultiply.c
        src/dataProcess.c
        src/getOperand2.c
        src/updateCPSR.c
        src/util.c
)

set(HEADER_FILES
        src/emulate.h
        src/decodeAndExecute.h
        src/branch.h
        src/dataTransfer.h
        src/checkCond.h
        src/printState.h
        src/iMultiply.h
        src/dataProcess.h
        src/getOperand2.h
        src/updateCPSR.h
        src/util.h
)

include_directories(src)

add_executable(emulate src/emulate.c ${SOURCE_FILES} ${HEADER_FILES})
#add_executable(assemble src/assemble.c ${SOURCE_FILES} ${HEADER_FILES})


set(TEST_SOURCE_FILES
        test/emulate/branch_test.c
        test/emulate/emulate_test.c
        test/emulate/printState_test.c
        test/emulate/util_test.c
)

set(TEST_HEADER_FILES
        test/emulate/branch_test.h
        test/emulate/util_test.h
)

include_directories(test)

#add_executable(runtests util_test.c ${TEST_SOURCE_FILES} ${TEST_HEADER_FILES} ${SOURCE_FILES} ${HEADER_FILES})
