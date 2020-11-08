#include "tsk.h"

entry_t* kth(const table_t* const table, const int position){

  return &table->entries[position];

}

entry_t** fromKtoNth(const table_t* const table, const int k, const int n){

  if(n > table->size) return NULL;

  entry_t** toReturn = (entry_t**)malloc(sizeof(entry_t)* (n-k));

  for (auto int i = 0; i < (n-k); ++i) toReturn[k+i] = &table->entries[k+i];

  return toReturn;

}

void printRange(const entry_t** const entry, const int n, const int k){

  for (auto int i = 0; i <(n-k) ; ++i)
    printf("%d th word is %s with an occurence of %u \n", k , entry[k + i]->value , entry[k + i]);

}

void readFromFile(const char* const fileName, table_t* table){

  FILE *fp = fopen(fileName, "r");

  if(!fp) fprintf(stderr,"error reading file. \n");

  char word[15];//long enough to hold the biggest word in the text?

  int position = 0;

  char ch;

  while((ch = fgetc(fp))!= EOF){

    //discard all the ascii chars that are not letters
    if(!(ch  >= 65 && ch <= 90) && !(ch >= 97 && ch <= 122)){

      word[position]= '\0';

      if(word[0] == NULL)continue;

      tableInsert(table, word);

      position = 0;

      continue;

    }
    else word[position++] = ch;
  }
}

void dev(const char* const fileName){

  table_t* table = tableInit(1024);

  readFromFile(fileName,table);

}

void prod(const char* const fileName){

  table_t* table = tableInit(1024);

  readFromFile(fileName,table);

}

int main(int argc, char** argv){

  auto int res = atoi(argv[1]);

  if(res == 0) dev(argv[2]);

  else prod(argv[2]);

  return 0;

}
