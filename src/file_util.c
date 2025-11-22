#include <file_util.h>
#include <stdio.h>
#include <stdlib.h>

FILE * open_file(const char * path) {
    FILE * file = fopen(path, "r");
    if(!file) {
        perror("Error opening file");
    }
    return file;
}

const char * file_to_char(FILE * file) {
    if(!file) return NULL;
    int read_size = 100;
    int counter = 0;
    char * read_inf = malloc(sizeof(char) * read_size);
    if(!read_inf) {
        perror("Error in allocation");
        return NULL;
    }
    for(;;) {
        int B_read = fread(read_inf + counter, sizeof(char), read_size - counter, file);
        counter += B_read;
        if(B_read < read_size - counter) break;
        read_size *= 2;
        char *tmp = realloc(read_inf, sizeof(char) * read_size);
        if(!tmp) {
            free(read_inf);
            perror("Error in allocation");
            return NULL;
        }
    }
    fclose(file);
    char *tmp = realloc(read_inf, sizeof(char) * counter + 1);
    if(!tmp) {
        free(read_inf);
        perror("Error in allocation");
        return NULL;
    }
    read_inf[counter] = '\0';
    return read_inf;
}

const char * file_read(const char * path) {
    return file_to_char(open_file(path));
}
