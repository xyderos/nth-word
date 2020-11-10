#include "table.h"
#include "entities.h"
#include <stdio.h>
#include <stdlib.h>

//initialise a new entry
entry_t* entryInit(const char* const value){

  unsigned int len   = strlen(value);
  entry_t* entry     = malloc(sizeof(entry_t));
  entry->value       = calloc(len, sizeof(char));
  entry->exists      = 1;
  entry->occurence   = 1;

  return entry;
}

//initialise a table
table_t* tableInit(const unsigned int size){

  table_t* table     = malloc(sizeof(table_t));
  table->entries     = calloc(size,sizeof(entry_t));
  table->seed        = getPrime();
  table->size        = size;
  table->usedEntries = 0U;

  return table;
}

//insert an item into a table
unsigned int tableInsert(table_t* table,const char* const value){

  unsigned int cutoff = (unsigned int)( 2 * (table->size / 2));
  //decide when to resize, might create a large enough array to bloat the memory?
  if(table->usedEntries >= cutoff ) tableResize(table, table->size*2);

  entry_t* entry = NULL;
  unsigned int index;
  auto unsigned int position = 0;

  while(position != table->size){

    //calculate hash of the string based on linear probing
    index = hashString(table->seed,value,table->size, position);
    //retrieve the entry of the table to check wether it exists or not
    entry = &table->entries[index];

    //entry doesnt exist so we write to them
    if(entry->exists == 0){

      *entry = *entryInit(value);
      table->usedEntries++;
      return index;

    }

    //item exists, might as well write on the position
    if(strcmp(entry->value, value) == 0){

      entry->occurence++;
      return index;

    }
    position++;
  }
  return -1;
}

//resize the table given, rehash all the items with the new linear probe
void tableResize(table_t *table, const unsigned int newSize) {

  // most likely wont happen but if there is an overflow then we have a problem
  if (table->size > newSize)
    return;

  // temp table that we store the results
  table_t *temp = tableInit(newSize);

  // copy the seed
  temp->seed = table->seed;

  // iterator-like entry
  entry_t *iterator;
  // index for the hash table
  unsigned int pos = 0;
  unsigned int index = 0;

  while (pos != table->size) {

    // get entry of the old table
    iterator = &table->entries[pos];
    // if it exists write it to the new table
    if (iterator->exists == 1) {

      index = tableInsert(temp, iterator->value);
      temp->entries[index].occurence = iterator->occurence;
    }
    pos++;
  }

  free(table->entries);

  table->entries = temp->entries;

  table->size = temp->size;

  table->usedEntries = temp->usedEntries;

}

int compFunc(const void *const a, const void *const b) {

  entry_t* t1 = (entry_t*)a;

  entry_t* t2 = (entry_t*)b;

  if(t1->exists==0 && t2->exists == 0){
    printf("both uninitialised , return 0 \n");
    return 0;
  }
  else if(t1->exists==1 && t2->exists == 0){

    printf("2nd entry doesnt exist, return -1 \n");
    return -1;

  }
  else if(t1->exists == 0 && t2->exists == 1){

    printf("1st entry doesnt exist, return -1 \n");
    return -1;

  }
  else return t1->occurence - t2->occurence;
}

void tableSort(table_t *table){

  qsort(table, table->size, sizeof(entry_t),compFunc);

}

// destroy a table, rule of thumb, call free for every malloc
void tableDestroy(table_t *table) {

  entry_t *entry = NULL;

  for (auto unsigned int i = 0; i < table->size; i++) {

    entry = &table->entries[i];

    if (entry->exists == 1) {

      free(entry->value);

      free(entry);
    }
  }

  free(table);
}
