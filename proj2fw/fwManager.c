
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fwManager.c
 *
 *
 */


#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/net.h>
#include <linux/syscalls.h>
#include "fwRBTree.c"




int isValidPort(unsigned short port, int protocol, int direction){
  
  return checkBlocked(&root, port, protocol, direction);

}

