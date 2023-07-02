/*
    Hashmap in C
    Copyright (C) 2023  Srivathsan Sudarsanan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "lib/hashmap.h"
#include <stdio.h>

void test_hash(hashmap *input_hashmap) {
  char test[][20] = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
  for (int i = 0; i < 8; i++) {
    insert_pair(input_hashmap, test[i], i + 1);
  }
}

int main() {
  hashmap *input_hashmap = create_hashmap();
  test_hash(input_hashmap);
  printf("items: %d\tcapacity: %d\n", input_hashmap->items,
         input_hashmap->capacity);
  delete_hashmap(input_hashmap);
  return 0;
}
