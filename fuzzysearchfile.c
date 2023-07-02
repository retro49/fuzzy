#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fuzzylist.h"
#include "fuzzydir.h"
#include "fuzzyfile.h"
#include "fuzzysearchfile.h"

void fuzzy_search_file_match(fuzstr name, fuzstr path, void* keys){
    Node* k = (Node*)keys; 
    while(k != NULL){
        fuzstr keyName = (fuzstr)k->n_data;
        // printf("matching %s <> %s\n", keyName, name);
        if(strstr(name, keyName)){
            printf("match found: %s\n",path);
        }

        k = k->n_next;
    }
}

void fuzzy_search_file(fuzstr path, void* files, void* intruders){
    fuzstr tempPath = malloc(sizeof(fuzchr) * 1024);
    if(!tempPath){
        printf("unable to allocate memory\n");
        return;
    }

    if(fuzzy_file_is_file(path)){
        printf("given path is not directory\n");
        return;
    }
    DIR* dir = opendir(path);
    if(!dir){
        printf("error opening dir\n");
        return;
    }

    struct dirent* info;
    while((info = readdir(dir)) != NULL){
        if(strcmp(info->d_name, ".") == 0 || strcmp(info->d_name, "..") == 0)
            continue;

        // here the work begins
        strcpy(tempPath, path);
        strcat(tempPath, "/");
        strcat(tempPath, info->d_name);

        printf("%s\n", tempPath);
        if(fuzzy_file_is_file(tempPath)){
            fuzzy_search_file_match(info->d_name, tempPath, files);
        }

        if(fuzzy_file_is_dir(tempPath)){
            boolean notIntruder = true;
            Node* intr = intruders;
            while(intr != NULL){
                if(strcmp(info->d_name, (fuzstr)intr->n_data) == 0){
                    notIntruder = false;
                    break;
                }
            }
            if(!notIntruder)
                continue;

            fuzzy_search_file(tempPath, files, intruders);
        }
    }

    // never forget to close something that has opened shithead.
    closedir(dir);

}
