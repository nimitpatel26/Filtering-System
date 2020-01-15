
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fwSyscalls.c
 * 
 * This file implements the syscalls related to the firewall.
 *
 */

#include <linux/errno.h>
#include <linux/syscalls.h>
#include "fwManager.c"


SYSCALL_DEFINE0(fw421_reset){
  
  if (current_cred()->uid.val != 0){
    return -EPERM;
  }
  reset(&root);
  return 0;
}

SYSCALL_DEFINE3(fw421_block_port, int, proto, int, dir, unsigned short, port){
  
  int index;
  int error;
  
  if (current_cred()->uid.val != 0){
    return -EPERM;
  }

  if (proto == 6){
    proto = 1;
  }else if (proto == 17){
    proto = 0;
  }
  
 
  index = getIndex(port, proto, dir);
  error = insert(&root, index);

  if (error != 0){
    return -EEXIST;
  }

  
  return 0;
}

SYSCALL_DEFINE3(fw421_unblock_port, int, proto, int, dir, unsigned short, port){
  
  int index;
  int error;
  
  if (current_cred()->uid.val != 0){
    return -EPERM;
  }  

  if (proto == 6){
    proto = 1;
  }else if (proto == 17){
    proto = 0;
  }
                                          
  
  index = getIndex(port, proto, dir);
  error = remove(&root, index);

  if (error != 0){
    return -ENOENT;
  }
  
  return 0;
}

SYSCALL_DEFINE3(fw421_query, int, proto, int, dir, unsigned short, port){
  

  int index;
  unsigned long ret;
  
  if (current_cred()->uid.val != 0){
    return -EPERM;
  }  


  if (proto == 6){
    proto = 1;
  }else if (proto == 17){
    proto = 0;
  }
 
  index = getIndex(port, proto, dir);
  ret = query(&root, index);

  if (ret == -1){
    return -ENOENT;
  }

  
  return ret;

}


/*
 * Debug system calls
 *
 */
SYSCALL_DEFINE3(fw421_check_blocked, int, proto, int, dir, unsigned short, port){
  
  int error;
  

  if (proto == 6){
    proto = 1;
  }else if (proto == 17){
    proto = 0;
  }

  error = checkBlocked(&root, port, proto, dir);

  if (error == -1){
    return -ENOENT;
  }

  return 0;

}

SYSCALL_DEFINE0(fw421_print_ports){
  
  printPorts(&root);
  return 0;
}
