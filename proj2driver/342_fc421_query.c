
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * 342_fc421_query.c
 *
 */


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_fc421_query 342


long fc421_query(const char* filename){
  return syscall(__NR_fc421_query, filename);
}

int main (int argc, char* argv[]){
  if (argc != 2){
    return EXIT_FAILURE;
  }
  const char* filename = argv[1];
  long query = fc421_query(filename);
  if (query == -1){
    printf("%s\n", strerror(query));
    return EXIT_FAILURE;
  }
  printf("%lu", query);
  return query;
}
