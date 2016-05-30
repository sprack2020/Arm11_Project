cmake_minimum_required(VERSION 3.5)
project(arm11_39)

set(CMAKE_C_FLAGS "-Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic")

# EMULATOR

set(SOURCE_FILES
        src/emulator/decodeAndExecute.c
        src/emulator/branch.c
        src/emulator/dataTransfer.c
        src/emulator/checkCond.c
        src/emulator/printState.c
        src/emulator/iMultiply.c
        src/emulator/dataProcess.c
        src/emulator/getOperand2.c
        src/emulator/updateCPSR.c
        src/util.c
)

set(HEADER_FILES
        src/emulate.h
        src/emulator/decodeAndExecute.h
        src/emulator/branch.h
        src/emulator/dataTransfer.h
        src/emulator/checkCond.h
        src/emulator/printState.h
        src/emulator/iMultiply.h
        src/emulator/dataProcess.h
        src/emulator/getOperand2.h
        src/emulator/updateCPSR.h
        src/util.h
)

include_directories(src)

add_executable(emulate src/emulate.c ${SOURCE_FILES} ${HEADER_FILES})

################################################################################
#EMULATOR

set(ASSEMBLER_SOURCE_FILES
        src/assembler/genInstr.c
        src/assembler/io.c
        src/assemble.c
        src/util.c
        src/assembler/assembler.c src/assembler/assembler.h)

set(ASSEMBLER_HEADERS
        src/assembler/io.h
        src/assembler/genInstr.h
        src/util.h
    )

add_executable(assemble src/assemble.c ${ASSEMBLER_SOURCE_FILES} ${ASSEMBLER_HEADER_FILES})

################################################################################
# TEST_EMULATOR

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
