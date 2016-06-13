//
// Created by drspaceship on 13/06/16.
//

// PRE: argv[1] is the input file to be compiled
// argv[2] is the output file location

#include <stdio.h>
#include <stdlib.h>
#include <compiler/compiler.h>

int main(int argc, char **argv) {

  if (argc != 2) {
    puts("Incorrect number of arguments");
    exit(EXIT_FAILURE);
  }
  Compiler_t compiler;
  init_compiler(&compiler, argv[1], argv[2]);
  compile(&compiler);
  deinit_compiler(&compiler);


  exit(EXIT_SUCCESS);
}