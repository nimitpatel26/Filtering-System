
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fwRBTree.c
 *
 */

#include <linux/rbtree.h>
#include <linux/slab.h>
#include <linux/spinlock.h>

struct rb_root root = RB_ROOT;

DEFINE_SPINLOCK(fwlock);

typedef struct blockedPort{
  struct rb_node node;
  int index;
  unsigned long attempts;
  
}BlkPort;

int getIndex(unsigned short port, int proto, int dir){
  int index = 0;
  index = port << 2;
  index = index + (proto << 1);
  index = index + dir;
  return index;
}

int getDirection(int index){
  index = index & 0x1;
  return index;
}

int getProtocol(int index){
  index = (index & 0x2) >> 1;
  return index;
}

unsigned short getPort(int index){
  unsigned short ret = (unsigned short) (index >> 2);
  return ret;
}


BlkPort* find(struct rb_root* root, int index){
  struct rb_node* node = root->rb_node;
  while (node){
    BlkPort* data = container_of(node, BlkPort, node);

    if (index < data->index){
      node = node->rb_left;
    }else if (index > data->index){
      node = node->rb_right;
    }else{
      return data;
    }
    

  }

  return NULL;
  
}


int insert(struct rb_root* root, int index){
  
  
  struct rb_node **new;
  struct rb_node *parent;
  BlkPort* data;
  
  spin_lock(&fwlock);
  
  data = (BlkPort*) kmalloc(sizeof(BlkPort), GFP_KERNEL);
  data->index = index;
  data->attempts = 0;
  
  
  new = &(root->rb_node);
  parent = NULL;
  
  while (*new){
    BlkPort* this = container_of(*new, BlkPort, node);
    parent = *new;

    if (data->index < this->index){
      new = &((*new)->rb_left);
    }else if (data->index > this->index){
      new = &((*new)->rb_right);
    }else{
      spin_unlock(&fwlock);
      return -1;
    } 
  }

  rb_link_node(&data->node, parent, new);
  rb_insert_color(&data->node, root);

  spin_unlock(&fwlock);
  return 0;

}


int remove(struct rb_root* root, int index){
  BlkPort* data;
  
  spin_lock(&fwlock);
  
  data = find(root, index);
 
  
  if (data){
    rb_erase(&data->node, root);
    kfree(data);
    spin_unlock(&fwlock);
    return 0;
  }

  spin_unlock(&fwlock);
  return -1;
  
}

unsigned long query(struct rb_root* root, int index){
  BlkPort* data;
  unsigned long ret;
  
  spin_lock(&fwlock);
  data = find(root, index);
  ret = 0;

  
  if (data){
    ret = data->attempts;
    spin_unlock(&fwlock);
    return ret;
  }

  spin_unlock(&fwlock);
  return -1;
}

void reset(struct rb_root* root){
  struct rb_node *node;
  
  spin_lock(&fwlock);
  
  node = rb_first(root);

  
  while (node){
    BlkPort* data = container_of(node, BlkPort, node);
    node = rb_next(node);
    rb_erase(&data->node, root);
    kfree(data);
  }

  spin_unlock(&fwlock);
  
}

int checkBlocked(struct rb_root* root, unsigned short port, int protocol, int direction){
  int index;
  BlkPort* data;
  
  spin_lock(&fwlock);
  
  index = getIndex(port, protocol, direction);
  data = find(root, index);

  

  if (data){
    data->attempts++;
    spin_unlock(&fwlock);
    return -1;
  }

  spin_unlock(&fwlock);
  return 0;  

}

void printPorts(struct rb_root* root){
  struct rb_node *node;

  spin_lock(&fwlock);
  
  node = rb_first(root);
  
  printk("Printing the list of blocked ports:\n");
  printk("Port\tProtocol\tDirection\tAttempts\n");
  
  while (node){
    BlkPort* data = container_of(node, BlkPort, node);
    node = rb_next(node);
    printk("%hu\t\t%d\t\t%d\t\t%lu\n", getPort(data->index), getProtocol(data->index), getDirection(data->index), data->attempts);
    
  }  

  spin_unlock(&fwlock);
}
