
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fcHT.c
 *
*/

#include <linux/hashtable.h>
#include <linux/slab.h>
#include <linux/spinlock.h>

// Number of bits in the hash table
#define NUM_OF_BITS 16
#define TABLE_SIZE 65423
#define HASH_TIMES 5

DEFINE_HASHTABLE(fcHT, NUM_OF_BITS);


DEFINE_SPINLOCK(fc_lock);

unsigned long fcHTSize = 0;

typedef struct blockedFile{
  char* filename;
  unsigned long count;
  unsigned long key;
  struct hlist_node node;
  
}BlkFile;

unsigned long hashFunction(const char* str, unsigned int length) {
  unsigned long hash = 0;
  unsigned int i = 0;
  
  for (; i < length; ++str, ++i){
    hash = (*str) + (hash << 6) + (hash << 16) - hash;
  }
  
  return hash;
}


unsigned long getKey(char* filename){
  unsigned long hash = hashFunction(filename, HASH_TIMES);
  int index = hash % TABLE_SIZE;
  return index;
}


BlkFile* findFile(char* filename){
  unsigned long key = getKey(filename);
  BlkFile* file;
  hash_for_each_possible(fcHT, file, node, key){
    
    if (strcmp(filename, file->filename) == 0){
      return file;
    }
  }
  return NULL;
}

int insertFile(char* filename){
  
  unsigned long key;
  BlkFile* newFile;
  
  spin_lock(&fc_lock);
  
  if (findFile(filename) != NULL){
    
    spin_unlock(&fc_lock);
    return -1;
  }
  
  key = getKey(filename);
  newFile = (BlkFile*) kmalloc(sizeof(BlkFile), GFP_KERNEL);
  newFile->filename = filename;
  newFile->count = 0;
  newFile->key = key;

  fcHTSize++;
  
  hash_add(fcHT, &newFile->node, key);
  spin_unlock(&fc_lock);
  return 0;
}

int removeFile(char* filename){
  BlkFile* file;
  
  spin_lock(&fc_lock);
  file = findFile(filename);
  if (file == NULL){
    
    spin_unlock(&fc_lock);
    return -1;
  }
  fcHTSize--;
  hash_del(&file->node);
  kfree(file->filename);
  kfree(filename);
  kfree(file);
  spin_unlock(&fc_lock);
  return 0;
}
unsigned long queryFile(char* filename){
  BlkFile* file;
  
  spin_lock(&fc_lock);
  file = findFile(filename);
  if (file == NULL){
    
    spin_unlock(&fc_lock);
    return -1;
  }

  spin_unlock(&fc_lock);
  return file->count;
  
}

unsigned long checkFileBlocked(char* filename){
  BlkFile* file;
  
  spin_lock(&fc_lock);
  file = findFile(filename);
  if (file == NULL){
    spin_unlock(&fc_lock);
    return 0;
  }

  
  file->count++;
  spin_unlock(&fc_lock);
  return 1;
}

void printFiles(void){
  
  int bkt;
  BlkFile* file;
  
  spin_lock(&fc_lock);
  
  printk("Printing the hashtable: \n");
  printk("Bucket\tKey\tFileName\tAttempts\n");
  hash_for_each(fcHT, bkt, file, node){
    printk("%d\t%lu\t%s\t%lu\n", bkt, file->key, file->filename, file->count);
  }
  spin_unlock(&fc_lock);
}


int resetHT(void){
  
  int bkt;
  BlkFile* file;
  BlkFile* prevFile;
  unsigned long counter;

  spin_lock(&fc_lock);
  
  if (hash_empty(fcHT)){
    spin_unlock(&fc_lock);
    return 0;
  }
  
  fcHTSize = 0;

  counter = 0;
  hash_for_each(fcHT, bkt, file, node){
    if (counter){
      hash_del(&prevFile->node);
      kfree(prevFile->filename);
      kfree(prevFile);
    }
    
    prevFile = file;
    counter++;
  }

  
  hash_del(&prevFile->node);
  kfree(prevFile->filename);
  kfree(prevFile);
  
  
  spin_unlock(&fc_lock);
  return 0;
}

