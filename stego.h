// stego.h contains declarations of constants, structs, functions, etc., common to both programs
// Stego_Wong-Chie_Joseph

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>


#define ERROR -1
#define OK 0

typedef struct
{
    char magic_number[3];
    int width;
    int height;
    int Maxval;
} ppm; 

// Function to validate command-line arguments and open the file
int validate_arguments(int argument_count, char** argument_values, int required_arguments, int file_index);

// Function to write the byte c to the stream referenced by fp
int write_hidden_byte(FILE *src, FILE *dst, char c);

// Function to write the msg message of length to the stream referenced by fp.
int write_hidden_msg(FILE *src, FILE *dst, int length, char *message);

// Writes the ppm header into new file dst
int write_header(FILE *dst, ppm pi);

// Function to read and return length of the hidden message
unsigned int read_msg_length(FILE *fp);

// Function to read the hidden message by reading the hidden characters
void read_hidden_msg(FILE *fp, int length, char *message);

// Function to read and parse the PPM header (magic number, comments, width, height, max value)
// Returns 0 on success, -1 if there is an error in the format
int read_header(ppm *pi, FILE *fp);

// Reads message
int readMsg(int argc, char **argv);

// Writes message
int writeMsg(int argc, char **argv);
