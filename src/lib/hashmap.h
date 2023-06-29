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
#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char key[20];
  int value;
} key_value_pair;

typedef struct {
  key_value_pair **pair;
  int items;
  int capacity;
} hashmap;

hashmap *create_hashmap();
key_value_pair *create_pair(char[20], int);
void delete_pair(key_value_pair *);
void delete_hashmap(hashmap *);
#endif
