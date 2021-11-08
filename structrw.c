#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

struct pop_entry {
  int year;
  int population;
  char boro[15];
};

int count_lines(){
  int o = open("nyc_pop.csv", O_RDONLY);
  char c;
  int count = 0;
  while ((read(o, &c ,1)) > 0){
    if (c == '\n'){
      count++;
    }
  }
  close(o);
  return count;
}

int count_commas(char *c){
  int count = 0;
    char *pch=strchr(c,',');
  while (pch!=NULL) {
    count++;
    pch=strchr(pch+1,',');
  }
  return count;
}

void read_csv(){
  char *test2;
  char *test3;
  int o = open("nyc_pop.csv", O_RDONLY);
  char test[1000];
  read(o, test, sizeof(test));
  int i;
  int j;
  // get header
  char borough[100];
  test2 = strchr(test , '\n');
  *test2++ = '\0';
  strcpy(borough, test);
  strcpy(test, test2);
  // get boroughs
  char boroughs[5][20];
  test2 = strchr(borough, ',');
  *test2++ = '\0';
  strcpy(borough, test2);
  int k = count_commas(borough);
  for (i = 0; i < k; i++){
    if (strchr(borough , ',') != NULL){
      test2 = strchr(borough, ',');
      *test2++ = '\0';
      strcpy(boroughs[i], borough);
      strcpy(borough, test2);
    }
  }
  strcpy(boroughs[k], borough);
  // make array
  struct pop_entry pop[(count_lines() - 1) * 5];
  int count = 0;
  for (i = 0; i < count_lines() - 1; i++){
    test2 = strchr(test , '\n');
    *test2++ = '\0';
    int year;
    int population[5];
    sscanf(test, "%d, %d, %d, %d, %d, %d", &year, &population[0], &population[1], &population[2], &population[3], &population[4]);
    for (j = 0; j < 5; j++){
      pop[count].year = year;
      pop[count].population = population[j];
      strcpy(pop[count].boro,boroughs[j]);
      count++;
    }
    /*char year[5];
    char population[5][100];
    sscanf(test, "%[^,], %[^,], %[^,], %[^,], %[^,], %s", year, population[0], population[1], population[2], population[3], population[4]);
    for (j = 0; j < 5; j++){
      pop[count].year = atoi(year);
      pop[count].population = atoi(population[j]);
      strcpy(pop[count].boro,boroughs[j]);
      count++;
    }*/
    strcpy(test, test2);
  }
  // write
  int file = open("nyc_pop.data", O_RDWR | O_CREAT | O_TRUNC, 0644);
  int written = write(file, pop, sizeof(pop));
  printf("read %lu bytes to nyc_pop.data\n", sizeof(pop));
}

void read_data(){
  int i;
  int file = open("nyc_pop.data", O_RDONLY);
  int file_size = lseek(file, 0, SEEK_END);
  file = open("nyc_pop.data", O_RDONLY);
  struct pop_entry pop2[file_size / sizeof(struct pop_entry)];
  read(file, pop2, file_size);
  for (i = 0; i < file_size / sizeof(struct pop_entry); i++){
    printf("year: %d\t population: %d\t borough: %s\n", pop2[i].year, pop2[i].population, pop2[i].boro);
  }
}

void add_data(){
  struct pop_entry add;
  int file = open("nyc_pop.data", O_WRONLY | O_APPEND, 0644);
  char data[100];
  printf("Enter data as Year Population Borough: \n");
  fgets(data, sizeof(data), stdin);
  sscanf(data, "%d %d %s", &add.year, &add.population, add.boro);
  int written = write(file, &add, sizeof(add));
}

void update_data(){
  int file = open("nyc_pop.data", O_RDWR);
  char entry[100];
  char data[100];
  struct pop_entry add;
  printf("Enter entry number: \n");
  fgets(entry, sizeof(entry), stdin);
  int number;
  sscanf(entry, "%d", &number);
  printf("Enter data as Year Population Borough: \n");
  fgets(data, sizeof(data), stdin);
  sscanf(data, "%d %d %s", &add.year, &add.population, add.boro);
  lseek(file, number * sizeof(struct pop_entry), SEEK_SET);
  write(file, &add, sizeof(struct pop_entry));
}
