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
