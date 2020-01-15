
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * 335_fw421_reset.c
 *
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_fw421_reset 335


long fw421_reset(void){
  return syscall(__NR_fw421_reset);
}

int main (int argc, char* argv[]){
 
  long err = fw421_reset();

  if (err){
    printf("%s\n", strerror((int) err));
    return EXIT_FAILURE;
  }
  return 0;
}
