#include <stdlib.h>
#include <stdio.h>

#include "table.h"

static inline entry_t*     kth(const table_t* const, const int);

static inline entry_t**    fromKtoNth(const table_t* const, const int, const int);

static inline void         printRange(const entry_t** const, const int, const int);

static inline void         readFromFile(const char* const, table_t*);

static inline void         dev(const char* const);

static inline void         prod(const char* const);
