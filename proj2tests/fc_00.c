
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fc_00.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>


#define __NR_fc421_reset 339
#define __NR_fc421_block_file 340
#define __NR_fc421_unblock_file 341
#define __NR_fc421_query 342


#define __NR_fc421_check_blocked 344
#define __NR_fc421_print_files 346


long fc421_reset(void){
  return syscall(__NR_fc421_reset);
}

long fc421_block_file(const char* filename){
  return syscall(__NR_fc421_block_file, filename);
}

long fc421_unblock_file(const char* filename){
  return syscall(__NR_fc421_unblock_file, filename);
}

long fc421_query(const char* filename){
  return syscall(__NR_fc421_query, filename);
}

long fc421_check_blocked(const char* filename){
  return syscall(__NR_fc421_check_blocked, filename);
}

long fc421_print_files(void){
  return syscall(__NR_fc421_print_files);
}
                                         
