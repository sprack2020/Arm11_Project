cmake_minimum_required(VERSION 3.5)
project(arm11_39)

set(CMAKE_C_FLAGS "-Wall -g -D_POSIX_SOURCE -D_BSD_SOURCE -std=c99 -Werror -pedantic")

# EMULATOR

set(EMULATOR_SOURCE_FILES
        src/emulator/decodeAndExecute.c
        src/emulator/branch.c
        src/emulator/dataTransfer.c
        src/emulator/checkCond.c
        src/emulator/global_state.c
        src/emulator/printState.c
        src/emulator/iMultiply.c
        src/emulator/dataProcess.c
        src/emulator/getOperand2.c
        src/emulator/updateCPSR.c
        src/util/util.c
        )

set(EMULATOR_HEADER_FILES
        src/emulate.h
        src/emulator/decodeAndExecute.h
        src/emulator/branch.h
        src/emulator/dataTransfer.h
        src/emulator/checkCond.h
        src/emulator/global_state.h
        src/emulator/printState.h
        src/emulator/iMultiply.h
        src/emulator/dataProcess.h
        src/emulator/getOperand2.h
        src/emulator/updateCPSR.h
        src/util/util.h
        )

include_directories(src)

add_executable(emulate src/emulate.c ${EMULATOR_SOURCE_FILES}
        ${EMULATOR_HEADER_FILES})

################################################################################
#ASSEMBLER

set(ASSEMBLER_SOURCE_FILES
        src/assembler/genInstr.c
        src/assembler/io.c
        src/util/util.c
        src/assembler/assembler.c
        src/util/ListMap.c
        src/util/ListMapNode.c
        src/util/ListMapIterator.c
        src/assembler/functionTable.c
        src/assembler/symbolTable.c
        src/assembler/tokenHandlers.c
        src/assembler/tokenizer.c
        src/assembler/assemblerStruct.h
        src/util/GenericListMapNode.c src/util/GenericListMapNode.h test/assemble/GenericListMap_String_FP_test.c test/assemble/GenericListMap_String_FP_test.h src/util/GenericListMap.c src/util/GenericListMap.h src/util/GenericListMapIterator.c src/util/GenericListMapIterator.h src/util/FunctionTable.c src/util/FunctionTable.h)

set(ASSEMBLER_HEADERS
        src/assembler/io.h
        src/assembler/genInstr.h
        src/util/util.h
        src/memory_util.h
        src/assembler/assembler.h
        src/util/ListMap.h
        src/util/ListMapNode.h
        src/util/ListMapIterator.h
        src/assembler/functionTable.h
        src/assembler/symbolTable.h
        src/assembler/tokenHandlers.h
        src/assembler/tokenizer.h
        )

add_executable(assemble src/assemble.c ${ASSEMBLER_SOURCE_FILES}
        ${ASSEMBLER_HEADER_FILES})

################################################################################
# EMULATOR TESTS

set(EMULATOR_TEST_SOURCE_FILES
        test/emulate/branch_test.c
        test/emulate/emulate_test.c
        test/emulate/printState_test.c
        test/emulate/util_test.c
        src/util/ListMap.c
        test/assemble/ListMapTests.c
)

set(EMULATOR_TEST_HEADER_FILES
        test/emulate/branch_test.h
        test/emulate/util_test.h
        test/assemble/ListMapTests.h
        src/util/ListMap.h
)

# ASSEMBLER TESTS
#
#set(TEST_ASSEMBLE_SRC
#        test/assemble/ListMapTests.c
#        test/assemble/test_assemble.c
#        )
#
#set(TEST_ASSEMBLE_HEADER
#        test/assemble/ListMapTests.h
#        )
#
#include_directories(test)
#
#add_executable(testassemble ${TEST_ASSEMBLE_SRC} ${TEST_ASSEMBLE_HEADER_FILES}
#        ${SOURCE_FILES} ${HEADER_FILES} ${ASSEMBLER_SOURCE_FILES}
#        ${ASSEMBLER_HEADER_FILES}
#        )
