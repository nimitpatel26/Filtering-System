
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * 336_fw421_block_port.c
 *
 */


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include "fw_get_data.c"

#define __NR_fw421_block_port 336


long fw421_block_port(int proto, int dir, unsigned short port){
  return syscall(__NR_fw421_block_port, proto, dir, port);
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

  //printf("Protocol: %d\n", proto);
  //printf("Direction: %d\n", dir);
  //printf("Port: %hu\n", port);
  
  long err = fw421_block_port(proto, dir, port);
  if (err){
    printf("%s\n", strerror(err));
    return EXIT_FAILURE;
  }
  return err;
}
