//stego.h contains declarations of constants, structs, functions, etc., common to both programs

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define FILE_OPEN_SUCCESS 1
#define FILE_OPEN_FAIL 0
#define PARSE_HEADER_SUCCESS 1
#define PARSE_HEADER_FAIL 0
#define EXIT_SUCCESS 0


struct msg 
{
    char *data;  // Pointer to the hidden message
    int length;  // Length of the hidden message
};

struct ppm 
{
    char magic_number[3];
    char comments[2];
    int width;
    int height;
    int Maxval;
    struct msg hidden_msg;
};

// Function to validate command-line arguments and open the file
int validate_arguments(int argument_count, char** argument_values, int required_arguments, int file_index);

// Function to parse header, checks and returns 1 if header begins with "P6\0" and returns 0 if otherwise
int parse_header(FILE *);

// Function to write the byte c to the stream referenced by fp
void write_hidden_byte(char, FILE *);

// Function to read and return length of the hidden message
unsigned int read_length(FILE *);

// Function to read a byte and returns it as a single character
unsigned int read_byte(FILE *);

// Function to read and parse the PPM header (magic number, comments, width, height, max value)
// Returns 0 on success, -1 if there is an error in the format
int readHeader(struct ppm *pi, FILE *fp);
