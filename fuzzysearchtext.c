#include <stdio.h>
#include <stdlib.h>
#include "fuzzyfile.h"
#include "fuzzysearchtext.h"

void fuzzy_search_text(fuzstr path, void* data){
    if(!fuzzy_file_exist(path))
        return;

    fuzzyfile file = fopen(path, "r");
    if(!file)
        return;
    // not even touched a little
}
