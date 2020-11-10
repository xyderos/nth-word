#include <stdio.h> //io
#include <stdlib.h>//memory management
#include <string.h>//compare functions

#include "entities.h"
#include "hash.h"

entry_t*            entryInit(const char* const);

table_t*            tableInit(const unsigned int);

unsigned int        tableInsert(table_t*, const char* const);

void                tableResize(table_t* ,const unsigned int);

int                 compFunc(const void * const, const void* const);

void                tableSort(table_t*);

void                tableDestroy(table_t*);
