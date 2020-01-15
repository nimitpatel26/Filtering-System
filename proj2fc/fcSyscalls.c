
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fcSyscalls.c
 * 
 * Implements the syscalls for the file control mechanism.
 *
 */

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/syscalls.h>
#include "fcManager.c"


char* copyFile(const char* filename){
  char* kfilename;
  int n = strlen(filename);
  
  if (n > 4096 || n == 0){
    return NULL;
  }
  n++;

  kfilename = kmalloc(n, GFP_KERNEL);
  if (copy_from_user(kfilename, filename, n) != 0){
    return NULL;
  }
  
  return kfilename;
}


SYSCALL_DEFINE0(fc421_reset){
  
  if (current_cred()->uid.val != 0){
    return -EPERM;
  }
  resetHT();
  return 0;
}

SYSCALL_DEFINE1(fc421_block_file, const char*, filename){

  char* kfilename;
  int err;
  
  if (current_cred()->uid.val != 0){
    return -EPERM;
  }
  
  kfilename = copyFile(filename);

  if (kfilename == NULL){
    return -EBADF;
  }
  
  
  err = insertFile(kfilename);

  if (err != 0){
    return -EEXIST;
  }
  
  return 0;
}

SYSCALL_DEFINE1(fc421_unblock_file, const char*, filename){

  char* kfilename;
  int err;


  if (current_cred()->uid.val != 0){
    return -EPERM;
  }

  kfilename = copyFile(filename);

  if (kfilename == NULL){
    return -EBADF;
  }      
  
  err = removeFile(kfilename);
  if (err != 0){
    return -ENOENT;
  }
  
  return 0;
}

SYSCALL_DEFINE1(fc421_query, const char*, filename){

  char* kfilename;
  unsigned long query;


  if (current_cred()->uid.val != 0){
    return -EPERM;
  }

  kfilename = copyFile(filename);

  if (kfilename == NULL){
    return -EBADF;
  }
                               


  
  query = queryFile(kfilename);

  if (query == -1){
    return -ENOENT;
  }
  
  
  return query;
}


/*
 * System calls used for debugging
 * 
 *
 */


SYSCALL_DEFINE1(fc421_check_blocked, const char*, filename){

  char* kfilename;
  
  if (current_cred()->uid.val != 0){
    return -EPERM;
  }

  kfilename = copyFile(filename);

  if (kfilename == NULL){
    return -EBADF;
  }

         
  
  checkFileBlocked(kfilename);
  return 0;
}

SYSCALL_DEFINE0(fc421_print_files){
  printFiles();
  
  
  return 0;
}
