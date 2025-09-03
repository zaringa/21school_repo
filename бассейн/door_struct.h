#ifndef SRC_DOOR_STRUCT_H_
#define SRC_DOOR_STRUCT_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DOORS_COUNT 15
#define MAX_ID_SEED 1000

struct door {
    int id;
    int status;
};

void initialize_doors(struct door* doors);
void sort_bobr_kyrva(struct door* doors);
void close(struct door* doors);
void out_door_run(struct door* doors);

#endif