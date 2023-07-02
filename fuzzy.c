// fuzzy main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "fuzzy.h"
#include "fuzzycolor.h"
#include "fuzzyconfig.h"
#include "fuzzydir.h"
#include "fuzzyfile.h"
#include "fuzzylist.h"
#include "fuzzysearchfile.h"

// arguments of fuzzy
i32 myArgc;
fuzstr* myArgv;

boolean fuzzy_arg_param_in(fuzstr arg){
    i32 iter = 0;
    while(iter < myArgc) 
        if(fuzzy_str_cmp(arg, *(myArgv + iter++)) == 0)
            return true;

    return false;
}

boolean fuzzy_arg_param_is_arg(fuzstr arg){
    return *arg == '-';
}

boolean fuzzy_arg_param_empty(){
    return myArgc == 0;
}

i32 fuzzy_arg_param_count(fuzstr arg){
    i32 total_param = 0;
    boolean arg_seen = false;
    for(int i = 0; i < myArgc; i++){
        fuzstr param = *(myArgv + i);
        if(arg_seen &&  *param == '-')
            break;

        if(fuzzy_str_cmp(arg, param) == 0){
            arg_seen = true;
            continue;
        }

        if(arg_seen)
            ++total_param;

    }

    return total_param;
}

void fuzzy_arg_param_parse(fuzstr arg, fuzstr* param_list, i32 param_len){
    if(!param_list)
        return;

    i32 param_count = 0, arg_count = 0;
    boolean parse_start = false;
    while(arg_count < myArgc){
        fuzstr param = *(myArgv + arg_count);
        if(fuzzy_str_cmp(arg, param) == 0 && !parse_start){
            parse_start = true;
            ++arg_count;
            continue;
        }

        if(parse_start && fuzzy_arg_param_is_arg(param))
            break;

        if(parse_start)
            *(param_list + param_count++) = param;
         
        ++arg_count;
    }
}

void __search_file(){
    i32 file_param_len;
    i32 directory_param_len;
    fuzstr file_arg;
    fuzstr* file_param;
    fuzstr* directory;
    if(fuzzy_arg_param_in(FUZ_PARAM_SHORT_FILE)){
        file_param_len = fuzzy_arg_param_count(FUZ_PARAM_SHORT_FILE);
        file_arg = FUZ_PARAM_SHORT_FILE;
    } else if(fuzzy_arg_param_in(FUZ_PARAM_LONG_FILE)){
        file_param_len = fuzzy_arg_param_count(FUZ_PARAM_LONG_FILE);
        file_arg = FUZ_PARAM_LONG_FILE;
    }

    if(file_param_len < 1){
        // error : must provide a file to search
        exit(FUZ_EXIT_CODE_ARG_NOT_PROVIDED);
    }

    file_param = (fuzstr*)fuzzy_param_malloc(sizeof(fuzstr) * file_param_len);
    if(!file_param){
        // throw error here, memory not allocated
        exit(FUZ_EXIT_CODE_MEM_ALLOC_ERR);
    }

    fuzzy_arg_param_parse(file_arg, file_param, file_param_len);
    // directory to search from
    if(!fuzzy_arg_param_in(FUZ_PARAM_DIR)){
        directory_param_len = 1;
        directory = (fuzstr*)fuzzy_param_malloc(sizeof(fuzstr));
        if(!directory){
            // error: exit 
            exit(FUZ_EXIT_CODE_MEM_ALLOC_ERR);

        }
        *(directory) = ".";
    } else{
        directory_param_len = fuzzy_arg_param_count(FUZ_PARAM_DIR);
        directory = (fuzstr*)fuzzy_param_malloc(sizeof(fuzstr) * directory_param_len);
        if(!directory){
            // error: exit
            exit(FUZ_EXIT_CODE_MEM_ALLOC_ERR);
        }
        fuzzy_arg_param_parse(FUZ_PARAM_DIR, directory, directory_param_len);
    }

    // not i do have both directories and files
    // so search 
    fuzzy_param_free(file_param);
    fuzzy_param_free(directory);
}

void __search_text(){
    i32 text_param_len;
    i32 directory_param_len;
    i32 arg_text_file_opt_len;
    fuzstr arg_text;
    fuzstr* text_param;
    fuzstr* arg_text_file_opt;
    fuzstr* directory_param;
    fuzstr* files; 
    if(fuzzy_arg_param_in(FUZ_PARAM_SHORT_TEXT)){
        text_param_len = fuzzy_arg_param_count(FUZ_PARAM_SHORT_TEXT);
        arg_text = FUZ_PARAM_SHORT_TEXT;
    } else if(fuzzy_arg_param_in(FUZ_PARAM_LONG_TEXT)){
        text_param_len = fuzzy_arg_param_count(FUZ_PARAM_LONG_TEXT);
        arg_text = FUZ_PARAM_LONG_TEXT;
    }

    if(text_param_len < 1){
        // must provide text to search
        // errror: nothing to search so...
    }

    // allocate memory for texts to search
    text_param = (fuzstr*)fuzzy_param_malloc(sizeof(fuzstr) * text_param_len);
    if(!text_param){
        // error: exit
    }
    fuzzy_arg_param_parse(arg_text, text_param, text_param_len);

    // get the directory
    if(!fuzzy_arg_param_in(FUZ_PARAM_DIR)){
        directory_param_len = 1;
        directory_param = (fuzstr*)fuzzy_param_malloc(sizeof(fuzstr));
        if(!directory_param){
            // error: exit
        }
        *(directory_param) = ".";
    } else {
        directory_param_len = fuzzy_arg_param_count(FUZ_PARAM_DIR);
        directory_param = (fuzstr*)fuzzy_param_malloc(sizeof(fuzstr) * directory_param_len);
        if(!directory_param){
            // error: exit
        }
        fuzzy_arg_param_parse(FUZ_PARAM_DIR, directory_param, directory_param_len);
    }

    // what type of file search 
    if(fuzzy_arg_param_in(FUZ_PARAM_SINGLE_FILE)){
        arg_text_file_opt = FUZ_PARAM_SINGLE_FILE;
        arg_text_file_opt_len = fuzzy_arg_param_count(FUZ_PARAM_SINGLE_FILE);
        files = (fuzstr*)fuzzy_param_malloc(sizeof(fuzstr) * arg_text_file_opt_len);
        if(!files){
            // error: text
        }

    } else if(fuzzy_arg_param_in(FUZ_PARAM_KEYWORD_FILE)){
        arg_text_file_opt = FUZ_PARAM_KEYWORD_FILE;
        arg_text_file_opt_len = fuzzy_arg_param_count(FUZ_PARAM_KEYWORD_FILE);
        files = (fuzstr*)fuzzy_param_malloc(sizeof(fuzstr) * arg_text_file_opt_len);
        if(!files){
            // error: exit
        }
    } else{
        arg_text_file_opt = FUZ_PARAM_ALL_FILE;
        arg_text_file_opt_len = fuzzy_arg_param_count(FUZ_PARAM_ALL_FILE);
    }

    fuzzy_param_free(text_param);
    fuzzy_param_free(directory_param);
    fuzzy_param_free(files);
}


void __search(){
 // search starts here
    if(fuzzy_arg_param_in(FUZ_PARAM_SHORT_FILE) || fuzzy_arg_param_in(FUZ_PARAM_LONG_FILE)){
        __search_file();
    }

    if(fuzzy_arg_param_in(FUZ_PARAM_SHORT_TEXT) || fuzzy_arg_param_in(FUZ_PARAM_LONG_TEXT)){
        __search_text();
    }

}

int main(int argc, char* argv[]){
    // reading file line by line test
    fuzzyfile theFile = fopen("./fuzzy.c", "r");
    if(!theFile){
        printf("file not found\n");
        return 1;
    }

    Node* linedata = fuzzy_file_readlines(theFile);
    if(!linedata){
        printf("empty line\n");
        return 1;
    }

    // iterate through the line and read
    Node* iter = linedata;
    while(iter != NULL){
        fuzstr data = (fuzstr)iter->n_data;
        printf("%c\n", *data);
        iter = iter->n_next;
    }

    /*
    fuzstr path = "/home/retro/Documents";
    Node* keys = fuzzy_malloc(sizeof(Node));
    Node* intruders = fuzzy_malloc(sizeof(Node));

    fuzzy_list_node_new(keys);
    fuzzy_list_node_add(keys, ".c");

    fuzzy_list_node_new(intruders);
    fuzzy_list_node_add(intruders, "fuzzy");

    fuzzy_search_file(path, keys, NULL);
    */

   /*
    Node* result = fuzzy_search_file_result;
    while(result != NULL){
        printf("%s\n", (fuzstr)result->n_data);
        result = result->n_next;
    }
    */

    /*
    Node* result = fuzzy_search_file_result;
    while(result != NULL){
        printf("%s\n", (fuzstr)result->n_data);
        result = result->n_next;
    }
    */

   /*
    myArgc = argc;
    myArgv = argv;
    // param test
    if(argc < 2){
        printf("%serror:%s not enough argument provided\n", COLOR_RED, COLOR_NORMAL);
        printf("%sterminating process...%s\n", COLOR_RED, COLOR_NORMAL);
        return FUZ_EXIT_CODE_NOT_ENOUGH_ARG;
    }

    if(fuzzy_arg_param_in(FUZ_PARAM_SHORT_VERBOSE) ||fuz_arg_param_in(FUZ_PARAM_LONG_VERBOSE)){
        fuzzy_config_verbose_mode(FUZZY_CONFIG_VERBOSE);
    }

    if(fuzzy_arg_param_in(FUZ_PARAM_SHORT_HELP) || fuz_arg_param_in(FUZ_PARAM_SHORT_HELP)){
        // print help and exit
    }

    if(fuzzy_arg_param_in(FUZ_PARAM_SHORT_SEARCH) || fuz_arg_param_in(FUZ_PARAM_LONG_SEARCH)){
        __search();
    }

    */
}

