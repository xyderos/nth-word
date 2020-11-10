#include <stdlib.h>
#include "entities.h"

int       less(int,int);

void      swap(entry_t*,entry_t*);

void      isort(table_t*,int,int);

int       partition(table_t*,int,int);

void      quicksort(table_t*,int,int);
