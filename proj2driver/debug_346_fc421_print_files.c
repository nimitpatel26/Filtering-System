
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * debug_346_fc421_print_files.c
 *
 */


#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_fc421_print_files 346


long fc421_print_files(void){
  return syscall(__NR_fc421_print_files);
}

int main (int argc, char* argv[]){
  fc421_print_files();
  return 0;
}
