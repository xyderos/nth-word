#include <time.h>

typedef unsigned int ul;

//generate a random 64 bit prime integer
static inline ul getPrime(){

  ul number;

  srand(time(NULL));

  number = rand();

  while(number % 2 != 0)number++;

  return number;

}

//algorithm based on djb2 , Dan Bernstein
static ul hash(ul seed ,char* key){

  ul hash = seed;

  int c;

  while(c = *key++) hash = ((hash<<5) + hash) + c; // hash * 33 + c

  return hash;
}

//iterable hashing with linnear probing
static ul hashIterable(ul seed, const char* const key, ul tableSize){

  ul position = hash(seed, key);

  return position % tableSize;

}
