// Stego_Wong-Chie_Jokan

#include "stego.h"

int writeMsg(int argc, char **argv)
{
    int status = 0;

    // Validate command-line arguments using validate_arguments function
    if ((status = validate_arguments(argc, argv, 4, 2)) == ERROR)
    {
        // If file validation fails, print the error message and exit
        printf("Error: Invalid arguments or file not found\n");
        return ERROR; // Exit with failure status
    }

    // If validation is successful, print success message
    printf("Command-line arguments validated successfully.\n");

    int length = strlen(argv[1]);

    char message[length];
    memcpy(message, argv[1], length);

    if (length > 255)
    {
        return ERROR;
    }

    FILE *original = fopen(argv[2], "rb");
    FILE *newf = fopen(argv[3], "wb");

    ppm pi = {};

    if (!(status = read_header(&pi, original)))
    {

        if ((pi.width * pi.height * 3) < length)
        {
            return ERROR;
        }

        if (pi.Maxval != 255)
        {
            return ERROR;
        }

        printf("Width:%d, Height:%d, MaxVal:%d\r\n", pi.width, pi.height, pi.Maxval);

        write_header(newf, pi);
        write_hidden_msg(original, newf, length, message);
    }
    else
    {
        fclose(original);
        fclose(newf);
        printf("Error. \n");
        return ERROR;
    }

    fclose(original);
    fclose(newf);

    return OK;
}

