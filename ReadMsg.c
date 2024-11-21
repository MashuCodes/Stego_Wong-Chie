// code here
#include "stego.c"
#include "stego.h"


int main(int argc, char **argv)
{
    unsigned int status = 0;
    unsigned int length = 0;

    // Validate command-line arguments using validate_arguments function
    if ((status = validate_arguments(argc, argv, 2, 1)) == FILE_OPEN_FAIL) 
    {
        // If file validation fails, print the error message and exit
        printf("Error: Invalid arguments or file not found\n");
        return EXIT_FAILURE;  // Exit with failure status
    }

    // If validation is successful, print success message and exit
    printf("Command-line arguments validated successfully.\n");

    FILE *fp = fopen(argv[1], "rb");

    if ((status = parse_header(fp)) == PARSE_HEADER_SUCCESS)
    {
        length = read_length(fp);
        printf("length: %d\n", length);
    }
    else {
        printf("Error. \n");
    }

    return EXIT_SUCCESS;  // Exit with success status
}
