//stego.c contains the implementation of functions common to both programs// code here

#include <stego.h>

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
    return FILE_OPEN_FAIL;
}

int parse_header(FILE *fp)
{
    
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
