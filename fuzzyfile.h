#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "fuzzytypes.h"

#ifndef FUZZYFILE
#define FUZZYFILE
typedef struct {
    i32 f_byte;
}Byte;

boolean fuzzy_file_is_file(fuzstr);
boolean fuzzy_file_is_dir(fuzstr);
boolean fuzzy_file_exist(fuzstr);
boolean fuzzy_file_is_link(fuzstr);

fuzstr fuzzy_file_read(fuzzyfile);
void* fuzzy_file_readlines(fuzzyfile);

#endif

