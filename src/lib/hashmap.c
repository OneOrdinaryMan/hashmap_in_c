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

unsigned int hash(char *key, int capacity) {
  unsigned int hash_num = 0;
  for (int i = 0; key[i] != '\0'; i++) {
    hash_num = hash_num + key[i];
  }
  while (1) {
    if (hash_num > 1000000) {
      break;
    }
    hash_num *= hash_num;
  }
  hash_num = (hash_num / 1000) % capacity;
  return hash_num;
}

void rehash(hashmap *input_hashmap) {
  if (input_hashmap->capacity - input_hashmap->items > 3) {
    return;
  }
  int new_capacity = input_hashmap->capacity + 10;
  key_value_pair **curr_pair = input_hashmap->pair;
  key_value_pair **new_pair =
      (key_value_pair **)malloc(sizeof(key_value_pair *) * new_capacity);
  for (int i = 0; i < input_hashmap->capacity; i++) {
    if (curr_pair[i] == NULL) {
      continue;
    } else {
      int hash_index = hash(curr_pair[i]->key, new_capacity);
      for (int j = 0; j < new_capacity; j++) {
        int try = (j + hash_index) % new_capacity;
        if (new_pair[try] == NULL) {
          new_pair[try] = curr_pair[i];
          break;
        }
      }
    }
  }
  input_hashmap->pair = new_pair;
  input_hashmap->capacity += 10;
  free(curr_pair);
}

void insert_pair(hashmap *input_map, char key[20], int value) {
  rehash(input_map);
  int hash_index = hash(key, input_map->capacity);
  key_value_pair *new_pair = create_pair(key, value);
  for (int i = 0; i < input_map->capacity; i++) {
    int try = (i + hash_index) % input_map->capacity;
    if (input_map->pair[try] == NULL) {
      input_map->pair[try] = new_pair;
      input_map->items++;
      return;
    }
  }
}

int search_pair(hashmap *input_hashmap, char *key) {
  int hash_index = hash(key, input_hashmap->capacity);
  for (int i = 0; i < input_hashmap->capacity; i++) {
    int try = (i + hash_index) % input_hashmap->capacity;
    key_value_pair *current_pair = input_hashmap->pair[try];
    if (current_pair == NULL) {
      continue;
    } else if (strcmp(current_pair->key, key) == 0) {
      return current_pair->value;
    }
  }
  printf("The value not found for the key %s.\n", key);
  return 0;
}

void search_delete(hashmap *input_hashmap, char *key) {
  int hash_index = hash(key, input_hashmap->capacity);
  for (int i = 0; i < input_hashmap->capacity; i++) {
    int try = (i + hash_index) % input_hashmap->capacity;
    key_value_pair *current_pair = input_hashmap->pair[try];
    if (current_pair == NULL) {
      continue;
    } else if (strcmp(current_pair->key, key) == 0) {
      delete_pair(current_pair);
      input_hashmap->pair[try] = NULL;
      input_hashmap->items--;
      return;
    }
  }
}

void print_table(hashmap *input_table) {
  for (int i = 0; i < input_table->capacity; i++) {
    if (input_table->pair[i] == NULL) {
      printf("---,---\n");
    } else {
      printf("%s, %d\n", input_table->pair[i]->key,
             input_table->pair[i]->value);
    }
  }
}
