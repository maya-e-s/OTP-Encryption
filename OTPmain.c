#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "read_file.h" //reads contents of a file to a char array; char *read_file(int len, char *file_name)
#include "write_file.h" //writes the complete contents of a string to a file; int write_file(int len, char *str, char *file_name)

char *make_rand_key(int len, char *key); //generate a fixed length string of random chars
void encrypt(char *clear_file, char *key_file, char *cipher_file); //produce cipher text string, write rand key and cipher text to file
void decrypt(char *key_file, char *cipher_file, char *message_file); //recover original text, write text to file

//contains driver code
int main() {
	int len;
	char *clear_file = malloc(30); //will be scanned in
	char *key_file = malloc(30);
	char *cipher_file = malloc(30);
	char *message_file = malloc(30);

	//user menu: loop with choice to encrypt, decyrpt, or exit
	int choice=1;
	while((choice==1) | (choice==2) | (choice==3)) {
		printf("Encrypt a file: 1\nDecrypt a file: 2\nExit:\t\t3\nEnter a choice: ");
		scanf("%d", &choice);
		switch(choice) {
			case 1: //Encrypt
				printf("Enter file name to encrypt: ");
				scanf("%s", clear_file);
				printf("Enter key file name to create: ");
				scanf("%s", key_file);
				printf("Enter cipher file name to create: ");
				scanf("%s", cipher_file);
				encrypt(clear_file, key_file, cipher_file);
				break;
			case 2: //Decrypt
				printf("Enter cipher file name: "); //encrypted file
				scanf("%s", cipher_file);
				printf("Enter key file name: "); //rand key file
				scanf("%s", key_file);
				printf("Enter decrypted file name to create: ");
				scanf("%s", message_file);
				decrypt(key_file, cipher_file, message_file);
				break;
			case 3: //leave loop and exit program
				exit(0);
			default:
				printf("Please choose a valid option.\n");
				break;
		}
	printf("\n");
	}
	//free allocated memory
	free(clear_file);
	free(key_file);
	free(cipher_file);
	free(message_file);
	return 0;
}

//generate fixed length string of random char
char *make_rand_key(int len, char *key) {
	int i, r;
	key = malloc(len+1);
	srand(time(NULL)); //seed rand()
	for(i=0;i<len;i++) {
		r = rand()%256; //scale between 0-255 --> unsigned char
		if (r == -1) //change EOF char (int value of -1)
			r=1;
		else if (r == 0) //change NULL char (int value of 0)
			r++;
		key[i] = (char)r; //cast r as char and add to array
	}
	key[i] = '\0';
	return key;
}

//produce cipher text string, write rand key and cipher text to file
void encrypt(char *clear_file, char *key_file, char *cipher_file) {
	//read clear_file
	char *clear_str = read_file(0,clear_file);
	//find length of string
	int len=0;
	int i=0;
	while(*(clear_str+i) != '\0') {
		len++;
		i++;
	}
	//make random string
	char *key;
	char *rand_str = make_rand_key(len, key);
	//perform the clear text XOR key text to produce cipher text
	char cipher_str[len];
	for(i=0;i<len;i++) {
		cipher_str[i] = *(clear_str+i) ^ *(rand_str+i);
	}
	//open files to write
	FILE *key_fname = fopen(key_file, "w");
	FILE *cipher_fname = fopen(cipher_file, "w");
	if (key_file == NULL) {
		printf("Key file cannot be opened\n");
		exit(0);
	}
	if (cipher_file == NULL) {
		printf("Cipher file cannot be opened\n");
		exit(0);
	}
	//write both random key and cipher text strings to file
	int key_len, cipher_len;
	key_len = write_file(len, rand_str, key_file);
	cipher_len = write_file(len, cipher_str, cipher_file);
	//print contents of files
	printf("The clear file '%s' holds the message '%s' (%d)\n", clear_file, clear_str, len);
	printf("The key file '%s' holds the text '%s' (%d)\n", key_file, rand_str, key_len);
	printf("The cipher file '%s' holds the text '%s' (%d)\n", cipher_file, cipher_str, cipher_len);
	//close files
	fclose(key_fname);
	fclose(cipher_fname);
}

//recover original text, write text to file
void decrypt(char *key_file, char *cipher_file, char *message_file) {
	//read key file
	char *key_str = read_file(0, key_file);
	//find length
	int i=0;
	int len=0;
	while (key_str[i] != '\0') {
		len++;
		i++;
	}
	//read cipher file
	FILE *cipher_fname = fopen(cipher_file, "r");
	if (cipher_file == NULL) {
		printf("Cipher file cannot be opened\n");
		exit(0);
	}
	char cipher_str[len+1];
	for (i=0;i<len;i++) {
		cipher_str[i] = getc(cipher_fname);
	}
	cipher_str[i] = '\0';
	//cipher text XOR random key to recover original clear text
	char message_str[len+1];
	for(i=0;i<len;i++) {
		message_str[i] = cipher_str[i] ^ key_str[i];
	}
	message_str[i] = '\0';
	//write clear text to file, using a different file name than the original to compare
	int len_message;
	len_message = write_file(0, message_str, message_file);
	printf("The decrypted file '%s' holds the message '%s' (%d)\n", message_file, message_str, len_message);
	//close file
	fclose(cipher_fname);
}
