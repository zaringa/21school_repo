#include "door_struct.h"

int main() {
    struct door doors[DOORS_COUNT];
    initialize_doors(doors);
    sort_bobr_kyrva(doors);
    close(doors);
    out_door_run(doors);
    return 0;
}

// Doors initialization function
// ATTENTION!!!
// DO NOT CHANGE!
void initialize_doors(struct door *doors) {
    srand(time(0));

    int seed = rand() % MAX_ID_SEED;
    for (int i = 0; i < DOORS_COUNT; i++) {
        doors[i].id = (i + seed) % DOORS_COUNT;
        doors[i].status = rand() % 2;
    }
}
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}
void sort_bobr_kyrva(struct door *doors) {
    int cur;
    for (int i = 0; i < DOORS_COUNT; i++) {
        cur = i;
        while (cur > 0 && doors[cur - 1].id > doors[cur].id) {
            swap(&(doors[cur - 1].id), &(doors[cur].id));
            cur--;
        }
    }
}

void out_door_run(struct door *doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        printf("%d, %d", doors[i].id, doors[i].status);
        if (i < DOORS_COUNT - 1) {
            printf("\n");
        }
    }
}
void close(struct door *doors) {
    for (int i = 0; i < DOORS_COUNT; i++) {
        if (doors[i].status) doors[i].status = 0;
    }
}
