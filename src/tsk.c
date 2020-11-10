#include "tsk.h"

void kth(const table_t* const table, const int position){

  entry_t* entry = NULL;

  entry = &table->entries[position];

  if(entry->exists == 1 ) printf("Nth most frequent word is %s with occurence %d . \n",entry->value, entry->occurence);

}

void fromKtoNth(const table_t* const table, const int k, const int n){

  for(auto int i = k; i < n;i++ )kth(table, i);

}

void readFromFile(const char* const fileName, table_t* table){

  FILE *fp = fopen(fileName, "r");

  char *buffer = NULL;

  unsigned long len = 0;

  int read = 0;

  char* token = NULL;

  while((read = getline(&buffer, &len, fp))!= -1 ){

    token = strtok(buffer, DELIMS);

    while(token !=NULL) {

      tableInsert(table, token);

      token = strtok(NULL, DELIMS);
    }
  }
}


int main(int argc, char** argv){

  if(argc != 2) return -1;

  table_t* table = tableInit(1024);

  printf("Building the HashTable for %s \n" , argv[1]);

  clock_t t = clock();

  readFromFile(argv[1],table);

  t = clock() - t;

  double elapsedTime = ((double)t)/CLOCKS_PER_SEC;

  printf("The table was built in %lf . \n", elapsedTime);

  printf("Sorting the Table using quick sort. \n");

  t = clock();

  tableSort(table);

  t = clock() - t;

  elapsedTime = ((double)t)/CLOCKS_PER_SEC;

  printf("The table was sorted in %lf \n", elapsedTime);

  unsigned int pos1;

  unsigned int pos2;

  for(;;){

    printf("Usage: When asked to insert a number, enter a non negative number and then again the same number to return the nth most frequent word. \n");
    printf("Usage: When asked to insert a number, enter a non negative number and then a different, bigger number to return a range of the most frequent words in this range. \n");
    printf("Usage: after you get your result type 0 to exit or 1 to continue running the program. \n");

    printf("Enter a number: \n");
    scanf("%d", &pos1);

    if(pos1 < 0 && pos1 > table->size){
     printf("Okay, try again big man. \n");
     continue;
    }

    printf("Enter a number: \n");
    scanf("%d", &pos2);

    if(pos2 < 0 && pos2 > table->size){
      printf("Okay, try again big man. \n");
      continue;
    }

    if(pos2-pos1 <0 ){
      printf("Okay, try again big man. \n");
      continue;

    }

    if(pos1-pos2 == 0) kth(table,pos1);

    else fromKtoNth(table,pos1,pos2);

    scanf("%d",&pos1);

    if(pos1 == 0 ) break;

  }

  printf("Thanks!!! \n");


  tableDestroy(table);

  return 0;
}
