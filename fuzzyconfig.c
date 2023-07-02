#include <stdio.h>
#include <stdlib.h>
#include "fuzzyconfig.h"

// verbose mode of operation
boolean fuzzy_config_verbose = FUZZY_CONFIG_NO_VERBOSE;
// set 
extern void fuzzy_config_verbose_mode(boolean mode){
    fuzzy_config_verbose = mode;
}

