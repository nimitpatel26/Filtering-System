
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fcManager.c
 *
 *
 */



#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/path.h>
#include <linux/dcache.h>
#include <linux/slab.h>
#include <linux/syscalls.h>


#include "fcHT.c"




const char* isValidPath(const char* path){

  if (checkFileBlocked(path) == 0){
    return path;
  }
  return NULL;
}

