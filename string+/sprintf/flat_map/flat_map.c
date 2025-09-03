#include "flat_map.h"

#include "../functions.h"

void init_flat_map(struct flat_map *map) {
  for (int i = 0; i < CHAR_COUNT; ++i) {
    map->types[i] = TYPES_COUNT;
  }

#define FILL_FUNC_ARR(name, fmt_char) map->functions[_##name] = format_##name;
  TYPES_LIST(FILL_FUNC_ARR)
#undef FILL_FUNC_ARR

#define FILL_TYPES_ARR(name, fmt_char) map->types[fmt_char] = _##name;
  TYPES_LIST(FILL_TYPES_ARR)
#undef FILL_TYPES_ARR
}

format_function get_function(struct flat_map *map, unsigned char type_char) {
  types type = map->types[type_char];
  return map->functions[type];
}
