#include <stdio.h>
#include <stdlib.h>
#include "read_file.h"

//reads contents of a file into a char array
char *read_file(int len, char *file_name) {
	//open file to read
	FILE *fname = fopen(file_name, "r");
	if (fname == NULL) { //if file is NULL print error and exit
		printf("File cannot be opened\n");
		exit(0);
	}

	//if len is unknown, get length from file read
	if (len == 0) {
		while(getc(fname) != EOF) {
			len++;
		}
	}

	//allocate memory to read file to a string
	char *str;
	str = malloc(len + 1); //add 1 for end of string or NULL char ('\0')
	if (str == NULL) {
		printf("Sufficient memory cannot be allocated\n");
		exit(0);
	}
	rewind(fname); //rewind file to beginning --> returns file pointer to beginning of file

	//read files content to allocated string
	int i;
	for(i=0;i<len;i++) {
		str[i] = getc(fname);
	}
	str[i] = '\0'; //end str with NULL char
	fclose(fname);
	return str;
}
