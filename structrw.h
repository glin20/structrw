struct pop_entry {
  int year;
  int population;
  char boro[15];
};
struct pop_entry *make_pop(int year, int population, char *boro);
int count_lines();
int count_commas(char *c);
void read_csv();
void read_data();
void add_data();
void update_data();
