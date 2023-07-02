#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "fuzzydir.h"
#include "fuzzyconfig.h"
#include "fuzzylist.h"
#include "fuzzyfile.h"

void* fuzzy_dir_listdir(fuzstr home){
    if(!fuzzy_file_exist(home))
        return NULL;
    if(!fuzzy_file_is_dir(home) || fuzzy_file_is_file(home))
        return NULL;

    Node* list = malloc(sizeof(Node));
    fuzzy_list_node_new(list);

    DIR* dir = opendir(home);
    if(!dir)
        return NULL;

    struct dirent* info;
    while((info = readdir(dir)) != NULL){
        if(strcmp((fuzstr)info->d_name, "." ) == 0 ||
           strcmp((fuzstr)info->d_name, "..") == 0 ){
            continue;
        }

        fuzzy_list_node_add(list, (fuzstr)info->d_name);
    }

    return list;
}
