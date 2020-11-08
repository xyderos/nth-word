#include <stdio.h> //io
#include <stdlib.h>//memory management
#include <string.h>//compare functions

#include "entities.h"
#include "hash.h"

static inline entry_t* entryInit(const char* const);

table_t* tableInit(const unsigned int);

table_t* tableResize(const table_t* const ,const unsigned int);

void tableInsert(table_t*, const char* const);

void tableCopyEntry(table_t*, entry_t*);

static inline void tableDestroy(const table_t* const);


