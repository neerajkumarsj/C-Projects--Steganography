#include "steganography.h"

int handle_error(int argc, char **argv)
{
    //1. Check for number of CLA
    if (argc < 3 || argc > 5)
    {
        printf("Invalid number of arguments.\n");
        printf("Encryption: \n");
        printf("<executable> <-e> <source_file_name> <destination_file_name>\n");
        printf("Destination: optional\n");
        printf("Decryption: \n");
        printf("<executable> <-d> <destination_file_name> <secret text filename>\n");
        printf("Secret text file: optional\n");
        return 1;
    }

    //2. Check for -d / -e
    if (argv[1][1] != 'd' && argv[1][1] != 'e')
    {
        printf("Invalid option.\n");
        printf("Enter\n-e: Encryption\n-d: Decryption\n");
        return 2;
    }

    //3. Check for the .bmp extension
    const char *p = argv[2] + (strlen(argv[2]) - 3);
    if (strcmp(p, "bmp") != 0)
    {
        printf("%s: Invalid File Format\n", argv[2]);
        printf("%s: Should have .bmp extension\n", argv[2]);
        return 3;
    }

    //4. Check for originality of the bmp file extension
    char buffer[2];

    FILE *fs = fopen(argv[2], "rb");
    if (fs == NULL)
    {
        perror("fs");
        return 4;
    }
    if (fread(buffer, 2, 1, fs) > 0)
    {
        if (buffer[0] != 0x42 && buffer[1] != 0x4d)
        {
            printf("%s: Is not an Original '.bmp' file\n", argv[2] );
        }
    }
    fclose(fs);
	return -1;
    //5. Validate .txt for secret file
    const char *q = argv[3] + (strlen(argv[3]) - 3);
    if (strcmp(p, "txt") != 0)
    {
        printf("%s: Invalid File Format\n", argv[3]);
        printf("%s: Should have .txt extension\n", argv[3]);
        return 5;
    }
    //6. Determine whether secret msg can be hidden inside the bmp file.
}

