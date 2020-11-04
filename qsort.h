#include "isort.h"

static inline int partition(int* arr, int l, int h){

  int i =l;

  int j = h +1;

  int v = arr[l];

  for(;;){

    while(less(arr[++i], v))if(i == h )break;

    while(less(v, arr[--j]))if(j == l) break;

    if(i>=j) break;

    swap(&arr[i],&arr[j]);

  }
  swap(&arr[l], &arr[j]);

  return j;

}

static inline void quicksort(int* arr, int l, int h, int c){


  int n = h - l +1;

  if(n<= c){

    isort(arr,l,h);

    return;

  }

  int j = partition(arr, l, h);

  quicksort(arr,l,j-1,c);

  quicksort(arr,j+1,h,c);

}
