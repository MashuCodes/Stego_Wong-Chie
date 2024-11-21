// Code here
#include "stego.h"
#include "stego.c"


void write_msg(FILE *fp, const char *message, unsigned int length)
{
    for (int i = 7; i >= 0; i--)
    {
        int bit = (length >> i) & 1;
        int pixel = fgetc(fp);
        if (pixel == EOF)
        {
            printf("Error \n");
            exit(1);
        }
        if (bit == 1)
        {
            pixel |= 1;
        }
        else
        {
            pixel &= 0xFE;
        }
        ungetc(pixel, fp);
    }
    for (unsigned int i = 0; i < length; i++)
    {
        unsigned char byte = message[i];
        for (int j = 7; j >= 0; j--)
        {
            int bit = (byte >> j) & 1;
            int pixel = fgetc(fp);
            if (pixel == EOF)
            {
                printf("Error \n");
                exit(1);
            }
            if (bit == 1)
            {
                pixel |= 1;
            }
            else
            {
                pixel &= 0xFE;
            }
            ungetc(pixel, fp);
        }
    }
}
