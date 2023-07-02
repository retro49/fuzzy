#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include "fuzzyfile.h"
#include "fuzzylist.h"

boolean fuzzy_file_is_dir(fuzstr dirname){
    struct stat dir;
    stat(dirname, &dir);
    return S_ISDIR(dir.st_mode);
}

boolean fuzzy_file_is_file(fuzstr filename){
    struct stat file;
    stat(filename, &file);
    return S_ISREG(file.st_mode);
}

boolean fuzzy_file_exist(fuzstr f){
    struct stat file;
    return stat(f, &file) == -1 ? false : true;
} 

boolean fuzzy_file_is_link(fuzstr f){
    struct stat file;
    lstat(f, &file);
    return S_ISLNK(file.st_mode);
}

u64 fuzzy_file_length(fuzzyfile file){
    if(!file)
        return -1;
    u64 fileLen = 0;
    i32 byte;
    while((byte = fgetc(file)) != EOF)
        ++fileLen;

    return fileLen;
}

fuzstr fuzzy_file_read(fuzzyfile file){
    if(!file)
        return NULL;
    fuzstr buffer;
    u64 bufferCounter;
    u64 bufferSize;
    i32 byte;

    bufferSize = fuzzy_file_length(file);
    buffer = fuzzy_malloc(sizeof(fuzchr) * bufferSize);
    if(!buffer)
        return NULL;

    rewind(file);
    while((byte = fgetc(file)) != EOF)
        *(buffer + bufferCounter++) = (char)byte;

    if(!feof(file))
        return NULL;

    if(ferror(file))
        return NULL;

    return buffer;
}

void* fuzzy_file_readlines(fuzzyfile file){
    if(!file)
        return NULL;
    rewind(file);
    Node* lines;
    Node* line;
    i32 byte;

    char* data;

    data = malloc(sizeof(char) * 1024);
    lines = fuzzy_malloc(sizeof(Node));
    line = fuzzy_malloc(sizeof(Node));
    if(!lines || !line){
        printf("unable to allocate line for file");
    }

    fuzzy_list_node_new(lines);
    rewind(file);

    u64 iter = 0;
    while((byte = fgetc(file)) != EOF){
        if(byte == 0x0A){
            fuzzy_list_node_add(lines, data);
            //free(data);
            data = malloc(sizeof(char) * 1024);
            iter = 0;
            continue;
        }

        *(data + iter) = (char)byte;
        iter = iter + 1;
    }

    if(!lines)
        return NULL;

    return lines;
}
