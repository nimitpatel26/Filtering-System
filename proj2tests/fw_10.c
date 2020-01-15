
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fw_10.c
 *
*/

#include "fw_00.c"

int main(){
  
  // protocol
  // direction
  // port
  fw421_reset();
  
  int dir[] = {0, 1};
  int proto[] = {IPPROTO_TCP, IPPROTO_UDP};
  unsigned short port[] = {0, 1, 2222, 65534, 65535};
  unsigned long ret = 0;
  
  printf("Blocking Ports:\n");
  printf("Protocol\tDirection\tPort\tReturn\n");
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
      for (int k = 0; k < 5; k++){
	ret = fw421_block_port(proto[i], dir[j], port[k]);
	printf("%d\t\t%d\t\t%hu\t%lu\n", proto[i], dir[j], port[k], ret); 
      }
    }
  }

  
  
  printf("\nQuerying Ports:\n");
  printf("Protocol\tDirection\tPort\tQuery\n");
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
      for (int k = 0; k < 5; k++){
	ret = fw421_query(proto[i], dir[j], port[k]);
	printf("%d\t\t%d\t\t%hu\t%lu\n", proto[i], dir[j], port[k], ret);
      }
    }
  }

  
  unsigned short attempts[] = {23, 11, 35, 8, 44, 45, 36, 28, 13, 9, 14, 50, 38, 26, 22, 6, 41, 12, 34, 46};
  printf("\nAttempting Ports:\n");
  printf("Protocol\tDirection\tPort\t# of Attempts\n");
  int tmp = 0;
  int counter = 0;
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
      for (int k = 0; k < 5; k++){
	tmp = attempts[counter];
	printf("%d\t\t%d\t\t%hu\t%lu\n", proto[i], dir[j], port[k], attempts[counter]);
	for (int l = 0; l < tmp; l++){
	fw421_check_blocked(proto[i], dir[j], port[k]);  
	}
	counter++;
	
      }
    }
  }  

  counter = 0;
  
  printf("\nQuerying Ports:\n");
  printf("Protocol\tDirection\tPort\tQuery\tMatch\n");
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 2; j++){
      for (int k = 0; k < 5; k++){
	ret = fw421_query(proto[i], dir[j], port[k]);
	printf("%d\t\t%d\t\t%hu\t%lu\t", proto[i], dir[j], port[k], ret);
	
	if (ret == attempts[counter]){
	  printf("YES\n");
	}else{
	  printf("NO\n");
	}
	
	counter++;
      }
    }
  }  
  

  
  //fw421_reset();
}
