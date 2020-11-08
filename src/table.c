#include "table.h"

static inline entry_t* entryInit(const char* const value){

  unsigned int len   = strlen(value);
  entry_t* entry     = malloc(sizeof(entry));
  entry->value       = malloc(sizeof(char*) * len);
  strncpy(entry->value, value, strlen(value));
  entry->exists      = 1;
  entry->occurence   = 1;

  return entry;

}

table_t* tableInit(const unsigned int size){

  table_t* table     = malloc(sizeof(table_t));
  table->entries     = malloc(size*sizeof(entry_t));
  table->seed        = getPrime();
  table->size        = size;
  table->usedEntries = 0U;

  return table;

}

table_t* tableResize(const table_t* const table, const unsigned int newSize){

  printf("resizing the table \n");
  if(table->size > newSize) return NULL;

  table_t* newTable     = tableInit(newSize);
  newTable->seed        = table->seed;
  newTable->usedEntries = table->usedEntries;
  entry_t* temp;

  //we iterate over the new table and we reinsert with the new hash code
  for (int i = 0; i < newTable->size; ++i){

    temp = &table->entries[i];

    //entry from the previous table exists, we rehash and keep the occurences
    if(temp->exists == 1) tableCopyEntry(newTable,temp);

  }

  tableDestroy(table);

  return newTable;

}

void tableCopyEntry(table_t* newTable, entry_t* previousEntry) {

  entry_t* entry = NULL;
  unsigned int index;
  auto int position = 0;

  while(position != newTable->size){

    index = hashString(newTable->seed,previousEntry->value,newTable->size, position);
    entry = &newTable->entries[index];

    if(entry->exists == 0){

      *entry = *entryInit(previousEntry->value);
      entry->occurence = previousEntry->occurence;
      free(previousEntry);

      return;

    } else{

      position++;

      continue;
    }
  }
}

void tableInsert(table_t* table,const char* const value){

  //decide when to resize, might create a large enough array to bloat the memory?
  if(table->usedEntries >= table->size/2 ) table = tableResize(table, table->size*2);

  entry_t* entry = NULL;
  unsigned int index;
  auto int position = 0;
  printf("Inserting  : %s :  " , value);

  while(position != table->size){

    //calculate the hash of our string as a function of the current position on the table
    index = hashString(table->seed,value,table->size, position); 
    printf("with hash number  %d . \n", index);
    entry = &table->entries[index];
    printf(" The value of this entry is %s . \n", entry->value);

    if(entry->exists == 0){

      printf(" It doesnt exist, so we create a new entry. \n");
      *entry = *entryInit(value);
      table->usedEntries++;
      break;

    } else if (entry->exists == 1 && strcmp(entry->value, value) == 0){

      printf(" It exists, so we increment its occurence. \n");
      entry->occurence++;
      break;

    } else{
      printf(" Entry exists and is a different word, go to the next iteration. \n");
      position++;
    }
  }
}

static inline void tableDestroy(const table_t* const table){

  for (auto int i = 0; i < table->size; ++i)
    if(&table->entries[i] !=NULL)free(&table->entries[i]);

  free(table);

}
