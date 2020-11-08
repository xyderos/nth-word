#pragma once

typedef struct __attribute__((packed)) __entry {

  char *value;

  unsigned int exists : 1;

  unsigned int occurence;

} entry_t;

typedef struct __table {

  int size;

  int usedEntries;

  entry_t *entries;

  unsigned int seed;

} table_t;
