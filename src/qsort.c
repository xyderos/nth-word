#include "qsort.h"

static inline int less(int a, int b){

  return (a<b) ? 1 : 0 ;

}

static inline void swap(entry_t* a,entry_t* b){

  entry_t* c = a;

  *a = *b;

  *b = *c;

}

static inline void isort(table_t * table, int l, int h){

  for(int i = l; i< h; i++)
    for(int j = i; j > l && less(table->entries[j].occurence, table->entries[j-1].occurence); j-- )
      swap(&table->entries[j], &table->entries[j-1]);

}

static inline int partition(table_t* arr, int l, int h){

  int i =l;

  int j = h +1;

  entry_t* v = &arr->entries[l];

  for(;;){

    while(less(arr->entries[++i].occurence, v->occurence))if(i == h )break;

    while(less(v->occurence, arr->entries[--j].occurence))if(j == l) break;

    if(i>=j) break;

    swap(&arr->entries[i],&arr->entries[j]);

  }
  swap(&arr->entries[l], &arr->entries[j]);

  return j;

}

static inline void quicksort(table_t* arr, int l, int h){

  if(h<l)return;

  int j = partition(arr, l, h);

  quicksort(arr,l,j-1);

  quicksort(arr,j+1,h);

}
