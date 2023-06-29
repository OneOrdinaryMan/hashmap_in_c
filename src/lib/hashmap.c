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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char key[20];
  int value;
} key_value_pair;

typedef struct {
  key_value_pair **pair;
  int items;
  int capacity;
} hashmap;

hashmap *create_hashmap() {
  hashmap *return_hashmap = malloc(sizeof(hashmap));
  int initial_capacity = 10;
  int initial_items = 0;
  return_hashmap->items = initial_items;
  return_hashmap->capacity = initial_capacity;
  return_hashmap->pair =
      (key_value_pair **)malloc(sizeof(key_value_pair *) * initial_capacity);
  for (int i = 0; i < return_hashmap->capacity; i++) {
    key_value_pair *current_pointer = *return_hashmap->pair + i;
    current_pointer = NULL;
  }
  return return_hashmap;
}
key_value_pair *create_pair(char key[20], int value) {
  key_value_pair *return_pair = malloc(sizeof(key_value_pair));
  snprintf(return_pair->key, 20, "%s", key);
  return_pair->value = value;
  return return_pair;
}
void delete_pair(key_value_pair *input_pair) {
  free(input_pair);
  input_pair = NULL;
}
void delete_hashmap(hashmap *input_hashmap) {
  for (int i = 0; i < input_hashmap->capacity; i++) {
    key_value_pair *current_pointer = input_hashmap->pair[i];
    if (current_pointer != NULL) {
      free(current_pointer);
      current_pointer = NULL;
    }
  }
  free(input_hashmap->pair);
  input_hashmap->pair = NULL;
  free(input_hashmap);
  input_hashmap = NULL;
}
