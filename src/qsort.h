#include <stdlib.h>

#include "entities.h"

static inline int  less(int,int);

static inline void swap(entry_t*,entry_t*);

static inline void isort(table_t*,int,int);

static inline int  partition(table_t*,int,int);

static inline void quicksort(table_t*,int,int);
