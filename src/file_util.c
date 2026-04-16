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

char * file_to_char(FILE * file) {
    if(!file) return NULL;
	fseek(file, 0, SEEK_END);
    size_t read_size = ftell(file) + 1;
	if(read_size > (size_t)1 << (sizeof(size_t) * 8 - 2) || read_size < 0) return NULL;
    char * read_inf = malloc(sizeof(char) * read_size);
    if(!read_inf) {
		fprintf(stderr, "Out of memory!\n");
        return NULL;
    }
	fseek(file, 0, SEEK_SET);
	size_t read_b = fread(read_inf, sizeof(char), read_size, file);
    read_inf[read_b] = '\0';
    return read_inf;
}

char * file_read(const char * path) {
	FILE *f = file_open(path);
	char *fc = file_to_char(f);
	fclose(f);
    return fc;
}
