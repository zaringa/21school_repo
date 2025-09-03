#include "help.h"

int main() {
  char file_path[100] = "../";
  char tmp_path[100];
  scanf("%99s", tmp_path);
  strcat(file_path, tmp_path);
  FILE *file = fopen(file_path, "rb");
  if (!file) {
    printf("n/a");
  } else {
    char search_date[11];
    scanf("%10s", search_date);
    struct reco rec;
    int found = 0;
    while (fread(&rec, sizeof(struct reco), 1, file) == 1) {
      char date[11];
      snprintf(date, sizeof(date), "%02d.%02d.%04d", rec.day, rec.month,
               rec.year);
      if (strcmp(date, search_date) == 0) {
        printf("%d", rec.code);
        found = 1;
        break;
      }
    }
    fclose(file);
    if (!found) {
      printf("n/a");
    }
  }
  return 0;
}