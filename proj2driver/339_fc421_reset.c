
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * 339_fc421_reset.c
 *
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_fc421_reset 339


long fc421_reset(void){
  return syscall(__NR_fc421_reset);
}

int main (int argc, char* argv[]){
  long err = fc421_reset();
  if (err){
    printf("%s\n", strerror(err));
    return EXIT_FAILURE;
  }
  return 0;
}
