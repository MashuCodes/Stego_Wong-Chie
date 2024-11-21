//stego.c contains the implementation of functions common to both programs// code here

#include "stego.h"

int validate_arguments(int argument_count, char **argument_values, int required_arguments, int file_index)
{
    // Check if the number of arguments is less than expected
    if (argument_count < required_arguments) 
    {
        printf("Usage error: %s missing required arguments\n", argument_values[0]);
        return FILE_OPEN_FAIL;
    }

    // Try to open the file for reading
    FILE *file = fopen(argument_values[file_index], "r");
    if (file == NULL) 
    {
        printf("Error: Unable to open the file %s for reading\n", argument_values[file_index]);
        return FILE_OPEN_FAIL;
    }

    // If no errors, return success
    return FILE_OPEN_SUCCESS;
}

int parse_header(FILE *fp)
{
    int c;

    // Loop to read the first two characters, checking for "P6"
    for (int i = 0; !isspace(c = getc(fp)) && i < 2; ++i)
     {
        if (i == 0 && c != 'P') 
        {  // Check the first character for 'P'
            return 0;  // Not a valid header if it doesn't start with 'P'
        }
        if (i == 1 && c != '6') 
        {  // Check the second character for '6'
            return 0;  // Not a valid P6 format if the second character isn't '6'
        }
    }

    return 1;  // Successfully read "P6" as the header
}

void write_hidden_byte(char c, FILE *fp) 
{
    char byte = 0;
    for(int i = 7; i >= 0; i--) 
    {
        byte = getc(fp);
        ungetc(0,fp);
        putc((byte & ~0x01) | ((c >> i) & 0x01), fp);
    }
}

unsigned int read_length(FILE *fp)
{
    unsigned int length = 0;
    for (int i = 0; i < 8; i++)
    {
        int pixel = fgetc(fp);
        if (pixel == EOF)
        {
            printf("Error while reading length. \n");
            exit(1);
        }
        length = length * 2 + (pixel & 1);
    }

    return length;
}

unsigned char read_byte(FILE *fp)
{
    int i;
    unsigned char byte = 0;

    for (i = 0; i < 8; ++i) 
    {
        // Read the next bit from the file
        int bit = fgetc(fp) & 0x01;  // Get the least significant bit

        // Shift the current bits in byte to the left by 1 position
        byte = (byte << 1) | bit;  // Append the bit to the byte
    }

    return byte;
}

char *read_hidden_msg(FILE *fp, int length) 
{
    // Allocate memory for the message (including space for null terminator)
    char *message = malloc((length + 1) * sizeof(char));
    if (message == NULL) 
    {
        perror("Memory allocation failed");
        return NULL;
    }

    // Read the hidden message byte by byte
    for (int index = 0; index < length; index++) 
    {
        message[index] = read_byte(fp);
    }

    // Null-terminate the string
    message[length] = '\0';

    return message;
}

int readHeader(struct ppm *pi, FILE *fp)
{
    int c;
    int *pm;

    for (int i = 0; !isspace(c = getc(fp)) && i < 2; ++i) {
        pi->magic_number[i] = c;
    }
    pi->magic_number[2] = '\0';

    if ((c = getc(fp)) == '#') {
        // comment processing
        pi->comments[0] = c;
        pi->comments[1] = '\0';
        // skip all comments
        while ((c = getc(fp)) != '\n')
            ;
    }
    else {
        // no commment
        ungetc(c, fp);
    }

    pi->width = pi->height = pi->Maxval = 0;
    pm = &pi->width;
    for (int i = 0; i < 3; i++) {
        while (!isspace(c = getc(fp))) {
            if (!isdigit(c)) {
                printf("corrupted format\n");
                return 1;
            }
            *pm = *pm * 10 + (c - '0');
        }
        ++pm;
    }

    return 0;
}
