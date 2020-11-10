#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "table.h"

static const char* const DELIMS = ", \' \" . ! ?  @ $ % ^ & * ; ";

static inline void         kth(const table_t* const, const int);

static inline void         fromKtoNth(const table_t* const, const int, const int);

static inline void         readFromFile(const char* const, table_t*);
