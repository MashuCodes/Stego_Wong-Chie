//stego.h contains declarations of constants, structs, functions, etc., common to both programs

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

// Function to parse header, checks and returns 1 if header begins with "P6\0" and returns 0 if otherwise
int parse_header(FILE *);

// Function to read the original file, and write the hidden byte onto the output file
void write_hidden_byte(char, FILE *);

// Function to read and return length of the hidden message
unsigned int read_length(FILE *);

// Function to read a byte and returns it as a single character
unsigned int read_byte(FILE *);
