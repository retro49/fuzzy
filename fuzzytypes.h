#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#ifndef FUZZY_TYPES
#define FUZZY_TPES
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;

typedef char i8;
typedef short i16;
typedef int i32;
typedef long i64;
typedef char fuzchr;
typedef fuzchr* fuzstr;
typedef unsigned char boolean;

#define true  1
#define false 0
#define fuzzyfile           FILE*
#define fuzzy_str_cmp       strcmp
#define fuzzy_param_malloc  malloc
#define fuzzy_param_free    free
#define fuzzy_node_malloc   malloc
#define fuzzy_node_free     free
#define fuzzy_malloc        malloc
#define fuzzy_free          free
#endif
