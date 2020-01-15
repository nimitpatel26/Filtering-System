
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * debug_344_fc421_check_blocked.c
 *
 */


#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_fc421_check_blocked 344


long fc421_check_blocked(const char* filename){
  return syscall(__NR_fc421_check_blocked, filename);
}

int main (int argc, char* argv[]){
  if (argc != 2){
    return -1;
  }
  const char* filename = argv[1];
  fc421_check_blocked(filename);
  return 0;
}
