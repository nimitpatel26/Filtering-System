
/*
 * Nimit Patel
 * CMSC 421
 * Project 2
 * fc_10.c
 *
*/

#include "fc_00.c"

int main(){
  
  // protocol
  // direction
  // port
  fc421_reset();


  char* filenames[20] = {"filename1","filename2", "filename3", "filename4", "filename5", "filename6", "filename7", "filename8", "filename9", "filename10", "filename11", "filename12","filename13", "filename14", "filename15", "filename16", "filename17", "filename18", "filename19", "filename20"};

  /*
  char **filenames = (char**) malloc(sizeof(char*) * 20);
 
  for (int i = 1; i <= 20; i++){
    char* tmp = (char*) malloc(sizeof(char) * 15);
    char* tmp2 = (char*) malloc(sizeof(char) * 10);
    tmp = "filename";



    sprintf(tmp2, "%d", i);
    
    strcat(tmp, tmp2);
    filenames[i-1] = &tmp;
    free(tmp2);
    }*/
 
  unsigned long ret = 0;
  
  printf("Blocking Files:\n");
  printf("Files\t\tReturn\n");
  for (int i = 0; i < 20; i++){
    
    ret = fc421_block_file(filenames[i]);
    printf("%s\t\t%lu\n", filenames[i], ret); 
      
    
  }


  
  ret = 0;
  printf("\nQuerying Files:\n");
  
  printf("Files\t\tReturn\n");
  for (int i = 0; i < 20; i++){
    ret = fc421_query(filenames[i]);
    printf("%s\t\t%lu\n", filenames[i], ret);
  }


               

  ret = 0;
  unsigned short attempts[] = {23, 11, 35, 8, 44, 45, 36, 28, 13, 9, 14, 50, 38, 26, 22, 6, 41, 12, 34, 46};
  printf("\nAttempting Files:\n");

  
  printf("Files\t\tAttempting\n");
  for (int i = 0; i < 20; i++){
    printf("%s\t\t%d\n", filenames[i], attempts[i]);
    for (int j = 0; j < attempts[i]; j++){
      ret = fc421_check_blocked(filenames[i]);
    }
  }


               

  ret = 0;
  printf("\nQuerying Files:\n");

  printf("Files\t\tReturn\t\tMatch\n");
  for (int i = 0; i < 20; i++){
    ret = fc421_query(filenames[i]);
    printf("%s\t\t%lu\t\t", filenames[i], ret);
    if (ret == attempts[i]){
      printf("YES\n");
    }else{
      printf("NO\n");
    }
    
  }

  /*
  for (int i = 0; i < 20; i++){
    free(filenames[i]);
  }
  
  free(filenames);*/
  //fw421_reset();
}
