
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * debug_345_fw421_reset.c
 *
 */


#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_fw421_print_ports 345


long fw421_print_ports(void){
  return syscall(__NR_fw421_print_ports);
}

int main (int argc, char* argv[]){
  fw421_print_ports();
  return 0;
}
