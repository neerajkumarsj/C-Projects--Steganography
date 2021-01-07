#include "steganography.h"

void decryption(char **argv)
{
    //Opening the files.
    FILE *fdest = fopen(argv[2], "rb");
    FILE *ftxt = fopen(argv[3], "w");

    //Handling File Opening Errors
    if (fdest == NULL || ftxt == NULL)
    {
        perror("fopen");
        exit(1);
    }

    int password;
    printf("Enter the Password: ");
    scanf("%d", &password);
    if (password == extract(fdest, 54))
    {
        puts("Password Accepted");
        int buff_size = extract(fdest, 86);
        decrypt(buff_size, fdest, ftxt, 118);
		
    }
    else
	{
		puts("Incorrect Password");
	}
	fcloseall();

}

void decrypt(int buff_size, FILE *fdest, FILE *ftxt, int seekpoint)
{
	char buffer[buff_size];
    int i;
    printf("String Decrypting");
    for (i = 0; i < buff_size; i++)
	{
		putchar('.');
		buffer[i] = char_extract(fdest, seekpoint);
		seekpoint = seekpoint + 8;
	}
	fputs(buffer, ftxt);

	puts("\nSuccessfully Decrypted");
	printf("String is %s", buffer);
}

int extract(FILE *fdest, int seekpoint)
{
    int i, buffer = 0;
    char val = 0;
    fseek(fdest, seekpoint, SEEK_SET);
    for (i = 0; i < 32; i++)
    {
        buffer = buffer << 1;
        fread(&val, 1, 1, fdest);
        if (val & 1)
        {
            buffer = buffer | 1;
        }
    }
    return buffer;
}

char char_extract(FILE *fdest, int seekpoint)
{
    char i, buffer = 0, val = 0;
    fseek(fdest, seekpoint, SEEK_SET);
    for (i = 0; i < 8; i++)
    {
        buffer = buffer << 1;
        fread(&val, 1, 1, fdest);
        if (val & 1)
        {
            buffer = buffer | 1;
        }
    }
    return buffer;
}
