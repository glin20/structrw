#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <strings.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include "structrw.h"

int main(int argc, char *argv[]){
  char action[100];
  printf("Enter Action: \n");
  fgets(action, sizeof(action) - 1, stdin);
  int i = 0;
  while (action[i]) {
    i++;
  }
  action[i-1] = 0;
  if (strcasecmp(action, "-read_csv") == 0){
    read_csv();
  }
  if (strcasecmp(action, "-read_data") == 0){
    read_data();
  }
  if (strcasecmp(action, "-add_data") == 0){
    add_data();
  }
  if (strcasecmp(action, "-update_data") == 0){
    update_data();
  }
}
