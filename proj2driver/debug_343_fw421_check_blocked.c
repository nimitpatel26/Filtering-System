
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * debug_343_fw421_check_blocked.c
 *
 */


#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include "fw_get_data.c"
                         
#define __NR_fw421_check_blocked 343


long fw421_check_blocked(int proto, int dir, unsigned short port){
  return syscall(__NR_fw421_check_blocked, proto, dir, port);
}

int main (int argc, char* argv[]){


  if (argc != 4){
    return -1;
  }

  int proto = getProtocol(argv[1]);
  int dir = getDirection(argv[2]);
  unsigned short port = 0;
  int portError = getPort(argv[3], &port);


  if (proto == -1 || dir == -1 || portError == -1){
    return -1;
  }
             
  fw421_check_blocked(proto, dir, port);
  return 0;
}
