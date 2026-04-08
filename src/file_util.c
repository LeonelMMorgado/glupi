#include <file_util.h>
#include <stdio.h>
#include <stdlib.h>

FILE * file_open(const char * path) {
    FILE * file = fopen(path, "rb");
    if(!file) {
        perror("Error opening file");
    }
    return file;
}

const char * file_to_char(FILE * file) {
    if(!file) return NULL;
	fseek(file, 0, SEEK_END);
    int read_size = ftell(file) + 1;
	if(read_size > 1 << 30) return NULL;
    int counter = 0;
    char * read_inf = malloc(sizeof(char) * read_size);
    if(!read_inf) {
		fprintf(stderr, "Out of memory!\n");
        return NULL;
    }
	fseek(file, 0, SEEK_SET);
    for(;;) {
        int B_read = fread(read_inf + counter, sizeof(char), read_size - counter, file);
        counter += B_read;
        if(B_read < read_size - counter) break;
    }
    fclose(file);
    read_inf[counter] = '\0';
    return read_inf;
}

const char * file_read(const char * path) {
    return file_to_char(file_open(path));
}
