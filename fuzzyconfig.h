#include "fuzzytypes.h"
#ifndef FUZZYCONFIG
#define FUZZYCONFIG
#endif

#define FUZZY_CONFIG_VERBOSE 1
#define FUZZY_CONFIG_NO_VERBOSE 0

// verbose config
extern boolean fuzzy_config_verbose;
extern void fuzzy_config_verbose_mode(boolean);
