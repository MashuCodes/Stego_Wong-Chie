// code here
#include "stego.h"

int readMsg(int argc, char **argv)
{
    int status = 0;
    unsigned int length = 0;

    // Validate command-line arguments using validate_arguments function
    if ((status = validate_arguments(argc, argv, 2, 1)) == ERROR)
    {
        // If file validation fails, print the error message and exit
        printf("Error: Invalid arguments or file not found\n");
        return ERROR; // Exit with failure status
    }

    // If validation is successful, print success message
    printf("Command-line arguments validated successfully.\n");

    FILE *fp = fopen(argv[1], "rb");
    ppm pi = {};

    if (!(status = read_header(&pi, fp)))
    {
        printf("Width:%d, Height:%d, MaxVal:%d\r\n", pi.width, pi.height, pi.Maxval);
        length = read_msg_length(fp);
        printf("Msg length: %d\n", length);
        if (length > 0)
        {
            char message[length+1];
            read_hidden_msg(fp, length, message);
            printf("Read Message: %s", message);
        }
    }
    else
    {   
        fclose(fp);
        printf("Error. \n");
        return ERROR;
    }

    fclose(fp);

    return OK; // Exit with success status
}
