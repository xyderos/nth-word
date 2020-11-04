#include "hashTable.h"
#include <string.h>

static entry_t* entryInit(const char* const value){

  entry_t* entry = (entry_t*)malloc(sizeof(entry));

  entry->value = "skata";

  entry->exists = 1;

  entry->occurence = 1;

  return entry;

}

static table_t* tableResize(const table_t* const table, const ul newSize){

  if(table->size > newSize) return NULL;

  table_t* newTable = tableInit(newSize);

  newTable->seed = table->seed;

  newTable->usedEntries = table->usedEntries + 1;

  entry_t* entry;

  printf("i was called \n");

  for (auto int i = 0; i < newTable->size; ++i)
    if(table->entries[i].exists)tableInsert(newTable,entry->value);

  tableDestroy(table);

  return newTable;

}

static table_t* tableInit(const ul size){

  table_t* table = (table_t*)malloc(sizeof(table_t));

  table->entries = (entry_t*)calloc(size, sizeof(entry_t));

  table->size = size;

  table->usedEntries = 0U;

  return table;

}

static void tableInsert(table_t* table,const char* const value){

  ul index = hashIterable(table->seed, value, table->size);

  entry_t* entry = &table->entries[index];

  printf("i am worth %ul bytes \n", sizeof(entry) );

  //our entry is empty and we can fill it
  if(!entry->exists){

    table->usedEntries++;

    table->entries[index].value = (char*)malloc(strlen(value));

    strcpy(table->entries[index].value, value);

    return;

  }
  //our position is filled thus we can increase the occurence
  else {

    table->usedEntries++;

    entry->occurence++;

    return;

  }

  table = tableResize(table, table->size * 2);

  printf("i ve been here \n");

  tableInsert(table,value);

}

static void tableDestroy(const table_t* const table){

  table_t* temp = table;

  for (auto int i = 0; i < temp->size; ++i)
    if(temp->entries[i].exists)free(&temp->entries[i]);

  free(temp);
}

static entry_t* kth(const table_t* const table, const ul position){

  return &table->entries[position];

}

static entry_t** fromKtoNth(const table_t* const table, const ul k, const ul n){

  if(n > table->size) return NULL;

  entry_t** toReturn = (entry_t**)malloc(sizeof(entry_t)* (n-k));

  for (auto int i = 0; i < (n-k); ++i) toReturn[k+i] = &table->entries[k+i];

  return toReturn;

}

static void printRange(const entry_t** const entry, const ul n, const ul k){

  for (auto int i = 0; i <(n-k) ; ++i) printf("%d th word is %s with an occurence of %u \n", k , entry[k + i]->value , entry[k + i]);

}

static inline int readFromFile(const char* const fileName, table_t* table){

  FILE *fp = fopen(fileName, "r");

  char word[35];//long enough to hold the biggest word in the text?

  int position = 0;

  char ch;

  while((ch = fgetc(fp))!= EOF){
    //we reached a punctuation point or an endline character
    //thus we have reached a word
    if( ch == '\n' || ch == ' ' || ch == '"' || ch == '-'||  ch == '?' || ch == '!' || ch == ',' || ch == '.'){

      word[position]= '\0';

      if(word[0] == NULL)continue;

      tableInsert(table, word);

      position = 0;

      continue;

    }
    else word[position++] = ch;

  }
}

int main(int argc, char** argv){

  //start by a relatively small table, such as 5000 words
  table_t* table = tableInit(2000);

  readFromFile(argv[1],table);

}
