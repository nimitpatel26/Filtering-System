
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fw_get_data.c
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define ZERO 48
#define ONE 49
#define NINE 57


int getData(char* a_data){
  char* tmp = malloc(1);
  *tmp = 0;
  strcpy(tmp, a_data);
  
  if (*tmp != ZERO && *tmp != ONE){
    free(tmp);
    return -1;
  }

  if (*tmp == ONE){
    free(tmp);
    return 1;
  }

  free(tmp);
  return 0;
}

int getProtocol(char* a_proto){
  // UDP == 0
  // TCP == 1
  char* tcp = "tcp";
  char* udp = "udp";
  
  if (strcmp(tcp, a_proto) == 0){
    return 1;
  }

  if (strcmp(udp, a_proto) == 0){
    return 0;
  }
  
  return -1;
}

int getDirection(char* a_dir){
  // out == 0
  // in == 1
  char* in = "in";
  char* out = "out";

  if (strcmp(out, a_dir) == 0){
    return 0;
  }

  if (strcmp(in, a_dir) == 0){
    return 1;
  }
  
  return -1;
}


int getPort(char* a_port, unsigned short* ret){
  char* port = malloc(6);
  unsigned short* portInt = (unsigned short*) malloc(sizeof(unsigned short));
  *portInt = 0;
  for (int i = 0; i < 6; i++){
    port[i] = 0;
  }

  strcpy(port, a_port);

  if (port[5] != '\0'){
    return -1;
  }
  
  int portLength = 0;
  int mul = 1;

  for (int i = 0; i < 5; i++){
    if (port[i] == 0){
      break;
    }
    if (port[i] < ZERO || port[i] > NINE){
      return -1;
    }
    portLength++;
    mul = (mul * 10);
  }

  mul = (mul / 10);

  for (int i = 0; i < portLength; i++){
    *portInt = (unsigned short) (*portInt + ((port[i]-'0') * mul));
    mul = (mul / 10);
  }

  *ret = *portInt;
  free(port);
  free(portInt);

  
  return 0;
}
