
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * 338_fw421_query.c
 *
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include "fw_get_data.c"
                         
#define __NR_fw421_query 338


long fw421_query(int proto, int dir, unsigned short port){
  return syscall(__NR_fw421_query, proto, dir, port);
}

int main (int argc, char* argv[]){


  if (argc != 4){
    return EXIT_FAILURE;
  }

  int proto = getProtocol(argv[1]);
  int dir = getDirection(argv[2]);
  unsigned short port = 0;
  int portError = getPort(argv[3], &port);


  if (proto == -1 || dir == -1 || portError == -1){
    return EXIT_FAILURE;
  }
             
  long err = fw421_query(proto, dir, port);
  if (err == -1){
    printf("%s\n", strerror(err));
    return EXIT_FAILURE;
  }
  printf("%lu\n", err);
  return err;
}
