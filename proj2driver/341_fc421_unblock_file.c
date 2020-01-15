
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * 341_fc421_unblock_file.c
 *
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_fc421_unblock_file 341


long fc421_unblock_file(const char* filename){
  return syscall(__NR_fc421_unblock_file, filename);
}

int main (int argc, char* argv[]){
  if (argc != 2){
    return EXIT_FAILURE;
  }
  const char* filename = argv[1];
  long err = fc421_unblock_file(filename);
  if (err){
    printf("%s\n", strerror(err));
    return EXIT_FAILURE;
  }           
  return err;
}
