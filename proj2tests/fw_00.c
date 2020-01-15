
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fw_00.c
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <netinet/in.h>
#include <sys/syscall.h>

#define __NR_fw421_reset 335
#define __NR_fw421_block_port 336
#define __NR_fw421_unblock_port 337
#define __NR_fw421_query 338

#define __NR_fw421_check_blocked 343
#define __NR_fw421_print_ports 345


long fw421_reset(void){
  return syscall(__NR_fw421_reset);
}

long fw421_block_port(int proto, int dir, unsigned short port){
  return syscall(__NR_fw421_block_port, proto, dir, port);
}

long fw421_unblock_port(int proto, int dir, unsigned short port){
  return syscall(__NR_fw421_unblock_port, proto, dir, port);
}

long fw421_query(int proto, int dir, unsigned short port){
  return syscall(__NR_fw421_query, proto, dir, port);
}

long fw421_check_blocked(int proto, int dir, unsigned short port){
  return syscall(__NR_fw421_check_blocked, proto, dir, port);
}

long fw421_print_ports(void){
  return syscall(__NR_fw421_print_ports);
}          
