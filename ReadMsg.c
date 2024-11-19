// code here
#include "stego.c"


int main(int argc, char **argv)
{
    unsigned int status = 0;

    // Validate command-line arguments using validate_arguments function
    if ((status = validate_arguments(argc, argv, 2, 1)) == FILE_OPEN_FAIL) 
    {
        // If file validation fails, print the error message and exit
        printf("Error: Invalid arguments or file not found\n");
        return EXIT_FAILURE;  // Exit with failure status
    }

    // If validation is successful, print success message and exit
    printf("Command-line arguments validated successfully.\n");

    return EXIT_SUCCESS;  // Exit with success status
}
