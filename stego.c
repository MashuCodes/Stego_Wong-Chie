// stego.c contains the implementation of functions common to both programs
// Stego_Wong-Chie_Joseph

#include "stego.h"

int validate_arguments(int argument_count, char **argument_values, int required_arguments, int file_index)
{
    // Check if the number of arguments is less than expected
    if (argument_count < required_arguments)
    {
        printf("Usage error: %s missing required arguments\n", argument_values[0]);
        return ERROR;
    }

    // Try to open the file for reading
    FILE *file = fopen(argument_values[file_index], "r");
    if (file == NULL)
    {
        printf("Error: Unable to open the file %s for reading\n", argument_values[file_index]);
        return ERROR;
    }

    fclose(file); // close the file

    // If no errors, return success
    return OK;
}


int read_header(ppm *pi, FILE *fp)
{
    int c;
    int *pm;

    // Read first 3 characters, parse magic number, if neither P or 6, return ERROR
    for (int i = 0; !isspace(c = getc(fp)) && i < 3; ++i)
    {
        if (c == 'P' || c == '6')
        {
            pi->magic_number[i] = c;
        }
        else
        {
            return ERROR;
        }
    }

    printf("%s ", pi->magic_number);
    // Comment parsing, ignores comments including denotor '#'
    if ((c = getc(fp)) == '#')
    {
        // skip all comments
        while ((c = getc(fp)) != '\n')
            ;
    }
    else
    {
        // no commment
        ungetc(c, fp);
    }

    // Gets values of width, height, and MaxVal (the maximum value of R, G, and B)
    pi->width = pi->height = pi->Maxval = 0;
    pm = &pi->width;
    for (int i = 0; i < 3; i++)
    {
        while (!isspace(c = getc(fp)))
        {
            if (!isdigit(c))
            {
                printf("corrupted format\n");
                return ERROR;
            }
            printf("%c", c);
            *pm = *pm * 10 + (c - '0'); // Moves up one decimal place (indicated by * 10) and adds the value of c(ASCII value) as a number
        }
        printf(" ");
        ++pm;
    }

    if (pi->Maxval != 255)
    {
        return ERROR;
    }

    return OK;
}

// Writes char c into least significant bits of a file src into dst
int write_hidden_byte(FILE *src, FILE *dst, char c)
{
    unsigned char byte = 0;
    for (int i = 7; i >= 0; i--)
    {
        byte = fgetc(src); // grabs new byte everytime
        fputc((byte & ~0x01) | ((c >> i) & 0x01), dst);
    }

    return OK;
}


int write_hidden_msg(FILE *src, FILE *dst, int length, char *message)
{

    if (length > 255)
    {
        return ERROR; // Msg too long to store length in 1 byte, exit.
    }

    write_hidden_byte(src, dst, length); // Calls write_hidden_byte function and writes length into first 8 bytes of dst file, similar to writing array size before using

    // Writes hidden message into dst
    for (int i = 0; i < length; i++)
    {
        write_hidden_byte(src, dst, message[i]);
    }

    // Copies rest of file after message is written, shopping bag analogy
    unsigned char buffer[1024];
    int bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), src))) // fread reads 1024 bytes of src 
    {
        fwrite(buffer, 1, bytes, dst); // fwrite writes the same 1024 bytes into dst
    }

    return OK;
}

// Writes the ppm header into new file dst
int write_header(FILE *dst, ppm pi)
{

    if (pi.height == 0 || pi.width == 0)
    {
        return ERROR;
    }
    if (pi.Maxval != 255)
    {
        return ERROR;
    }

    fprintf(dst, "%s\n%d %d\n%d\n", pi.magic_number, pi.width, pi.height, pi.Maxval); // adds formatted header stored in pi to dst file

    return OK;
}

// Reads and returns length of hidden message
unsigned int read_msg_length(FILE *fp)
{
    unsigned int length = 0;
    for (int i = 0; i < 8; i++)
    {
        int pixel = fgetc(fp);
        if (pixel == EOF)
        {
            printf("Error while reading length. \n");
            length = -1;
        }
        length = length * 2 + (pixel & 0x1); // Build's length using base 2 arithmetic
    }

    return length;
}


unsigned char read_hidden_byte(FILE *fp)
{
    int i;
    unsigned char byte = 0;

    for (i = 0; i < 8; ++i)
    {
        // Read the next bit from the file
        int bit = fgetc(fp) & 0x01; // Get the least significant bit

        // Shift the current bits in byte to the left by 1 position
        byte = (byte << 1) | bit; // Append the bit to the byte
    }

    return byte;
}


void read_hidden_msg(FILE *fp, int length, char *message)
{
    // Read the hidden message byte by byte
    for (int index = 0; index < length; index++)
    {
        message[index] = read_hidden_byte(fp);
    }

    // Null-terminate the string
    message[length] = '\0';
}
