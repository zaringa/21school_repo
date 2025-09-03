#ifndef FLAT_MAP_H
#define FLAT_MAP_H

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>

#include "../defs.h"

struct flat_map {
  char types[CHAR_COUNT];
  format_function functions[TYPES_COUNT];
};

void init_flat_map(struct flat_map *);

format_function get_function(struct flat_map *map, unsigned char type);

#endif
