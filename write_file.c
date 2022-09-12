#include <stdio.h>
#include <stdlib.h>
#include "write_file.h"

//writes the complete contents of a string to a file
int write_file(int len, char *str, char *file_name) {
	//open file to write
	FILE *fname = fopen(file_name, "w");
	if (file_name == NULL) {
		printf("Write file cannot be opened\n");
		exit(0);
	}
	//if len is unknown, read str until '\0' is reached
	int i=0;
	if (len == 0) {
		while(*(str+i) != '\0') {
			len++;
			i++;
		}
	}
	//write string to file
	for (i=0; i<len; i++) {
		putc(str[i], fname); //fputs() can also be used
	}
	//close file
	fclose(fname);
	return len;
}
