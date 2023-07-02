#include <stdio.h>
#include <stdlib.h>
#include "fuzzytypes.h"
#include "fuzzydir.h"
#include "fuzzyfile.h"
#include "fuzzyconfig.h"

#ifndef FUZZY_SEARCH_FILE
#define FUZZY_SEARCH_FILE


void fuzzy_search_file_match(fuzstr, fuzstr, void*);
void fuzzy_search_file(fuzstr, void*, void*);

#endif
