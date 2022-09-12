# One Time Pad Encryption/Decryption
C program to read and write files while implementing One Time Pad (OTP) encryption and decryption.

## OTP Encryption
When implemented properly, OTP cannot be hacked by cryptanalysis. This method uses the clear text (message to be encrypted), a random key of characters (the same size of the clear text) and the exclusive OR (XOR) operator. 

## Files
### read_file
Reads the complete contents of a file to a string.

### write_file
Writes the complete contents of a string to a file.

### OTPmain.c
Prompts user to encrypt a file, decrpyt a file, or exit program.
Encrypting a file prompts the user to enter a filename of the clear text along with filenames to save the random key and cipher text. It generates a random key, produces the cipher text string by performing byte-by-byte XOR between the clear text and random key, and writes both the random key and cipher text strings to a file.
Decrypting a file prompts the user to enter the filename of the random key as well as a filename to store the recovered text into. It recovers the clear text by performing XOR between the cipher text and random key, and writes the recovered clear text to a file.
If memory allocation or file open is unsuccessful, an error message is printed and the program is terminated.

## Compile and Run
To run this program, I am running an Ubuntu terminal through Windows Subsystem for Linux (WSL). I am using the GNU Nano Text Editor and a GCC Compiler.
To link the files and compile and run the program, I ran the commands

     nano OTPmain.c &
     nano read_file.h &
     nano read_file.c &
     nano write_file.h &
     nano write_file.c &
     gcc OTPmain.c read_file.c write_file.c -o OTPmain
     ./OTPmain
