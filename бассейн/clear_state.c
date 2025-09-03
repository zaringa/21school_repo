#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int status;
  int code;
} reco;

int compare(const reco *record, const int year, const int month,
            const int day) {
  int res = 0;
  if (record->year < year) {
    res = -1;
  } else if (record->year > year) {
    res = 1;
  } else if (record->month < month) {
    res = -1;
  } else if (record->month > month) {
    res = 1;
  } else if (record->day < day) {
    res = -1;
  } else if (record->day > day) {
    res = 1;
  }
  return res;
}

void print_record(const reco *record) {
  printf("%d %d %d %d %d %d %d %d\n", record->year, record->month, record->day,
         record->hour, record->minute, record->second, record->status,
         record->code);
}

void printr(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file != NULL) {
    reco record;
    while (fread(&record, sizeof(reco), 1, file) == 1) {
      print_record(&record);
    }
    fclose(file);
  } else {
    printf("n/a");
  }
}

int main() {
  FILE *file, *tempFile;
  char tempFilename[] = "temp.dat";
  reco record;
  int startYear, startMonth, startDay;
  int endYear, endMonth, endDay;
  int found = 0;
  char filename[100] = "../";
  char tmp_path[100];
  scanf("%99s", tmp_path);
  strcat(filename, tmp_path);
  file = fopen(filename, "rb");
  tempFile = fopen(tempFilename, "wb");
  if (file == NULL || tempFile == NULL) {
    printf("n/a");
    if (file != NULL) {
      fclose(file);
    }
    if (tempFile != NULL) {
      fclose(tempFile);
      remove(tempFilename);
    }
  } else {
    if (scanf("%d.%d.%d %d.%d.%d", &startDay, &startMonth, &startYear, &endDay,
              &endMonth, &endYear) != 6) {
      printf("n/a");
      fclose(file);
      fclose(tempFile);
    } else {
      while (fread(&record, sizeof(reco), 1, file) == 1) {
        if (compare(&record, startYear, startMonth, startDay) < 0 ||
            compare(&record, endYear, endMonth, endDay) > 0) {
          fwrite(&record, sizeof(reco), 1, tempFile);
        } else {
          found = 1;
        }
      }
      fclose(file);
      fclose(tempFile);
      if (!found) {
        printf("n/a");
        remove(tempFilename);
      } else {
        if (remove(filename) == 0 && rename(tempFilename, filename) == 0) {
          printr(filename);
        } else {
          printf("n/a");
        }
      }
    }
  }
  return 0;
}