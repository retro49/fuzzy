/*
 * The GPLv3 License (GPLv3)

 Copyright (c) 2023 Author

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <stdio.h>
#include <stdlib.h>
#include "fuzzytypes.h"

#ifndef FUZFILE
#define FUZFILE 

#define FUZ_PARAM_SHORT_SEARCH "-s"
#define FUZ_PARAM_SHORT_TEXT   "-t"
#define FUZ_PARAM_SHORT_FILE   "-f"
#define FUZ_PARAM_SHORT_VERBOSE "-v"
#define FUZ_PARAM_SHORT_HELP    "-h"

#define FUZ_PARAM_LONG_SEARCH  "--search"
#define FUZ_PARAM_LONG_TEXT    "--text"
#define FUZ_PARAM_LONG_FILE    "--file"
#define FUZ_PARAM_LONG_VERBOSE "--verbose"
#define FUZ_PARAM_LONG_HELP    "--help"
#define FUZ_PARAM_DIR          "-d"
#define FUZ_PARAM_ALL_FILE     "-af"
#define FUZ_PARAM_SINGLE_FILE  "-sf"
#define FUZ_PARAM_KEYWORD_FILE "-kf"

#define FUZ_EXIT_CODE_NOT_ENOUGH_ARG    1 
#define FUZ_EXIT_CODE_MEM_ALLOC_ERR     2
#define FUZ_EXIT_CODE_ARG_NOT_PROVIDED  3

void __search();
void __search_file();
void __search_text();

// checks if a given argument is in argv
boolean fuzzy_arg_param_in(fuzstr);

// checks if a given string is argument or not
boolean fuzzy_arg_param_is_arg(fuzstr);

// checks argument length
boolean fuzzy_arg_param_empty(); 

// counts parameter for an argument
i32 fuzzy_arg_param_count(fuzstr);

// parses an argument
// arg, argv, argc, param_list, param_len
void fuzzy_arg_param_parse(fuzstr, fuzstr*, i32);

#endif

