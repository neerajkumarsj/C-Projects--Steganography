#include "steganography.h"

void encryption(char **argv)
{
	char byte;
    //Open the Files
    FILE *fsrc= fopen(argv[2], "rb");
    FILE *ftxt = fopen(argv[3], "r");
    FILE *fdest = fopen(argv[4], "wb");
    
    //Handling File Opening Errors
    if (fsrc == NULL || ftxt == NULL || fdest == NULL)
    {   
        perror("fopen");
        exit(1);
    }   
  
    char buffer[100];
    fread(buffer, 54, 1, fsrc);
    fwrite(buffer, 54, 1, fdest);
    puts("Successfully Copied Header!");
    
    //Password Creation
    int password = random() % 10000;
    printf("Password: %d\n", password);
    
    //Password Encryption
    puts("Encrypting Message and Password");
    puts("_______________________________");
    bit_crypting(password, fdest, fsrc, 54); 
	
	//Message Encryption
	memset(buffer, '\0', 100);
	message_crypting(buffer, 100, fdest, ftxt, fsrc, 86);
    puts("\nSuccessfully Encrypted.");
    
    while (fread(&byte, 1, 1, fsrc) > 0)
	{
		fwrite(&byte, 1, 1, fdest);
	}

    fcloseall();

}


void bit_crypting(int enc_val, FILE *fdest, FILE *fsrc, int seekpoint)
{
	//Declaring mask and variable to store the Encrypted Byte
    unsigned mask;
    unsigned char val;

    //Pointer to point at the given Seek Point
    fseek(fsrc, seekpoint, SEEK_SET);
    for (mask = 1 << (sizeof(int)*8 - 1); mask; mask >>= 1)
    {
        fread(&val, 1, 1, fsrc);
        if (enc_val & mask)
        {
            val = val | 1;
        }
        else
        {
            val = val & 0;
        }
        fwrite(&val, 1, 1, fdest);
    }  
}

void bit_char_crypting(char enc_val, FILE *fdest, FILE *fsrc, int seekpoint)
{
	//Declaring mask and variable to store the Encrypted Byte
    unsigned char mask;
    char val;
    
    //Pointer to point at the given Seek Point
    fseek(fsrc, seekpoint, SEEK_SET);
    for (mask = 1 << 7; mask; mask >>= 1)
    {
        fread(&val, 1, 1, fsrc);
        if (enc_val & mask)
        {
            val = val | 1;
        }
        else
        {
            val = val | 0xFE;
        }
        fwrite(&val, 1, 1, fdest);
    }  
}
  
void message_crypting(char *buffer, int len, FILE *fdest, FILE *ftxt, FILE *fsrc, int seekpoint)
{
	int str_len, i, temp;
	//Handling Errors
	if (fgets(buffer, len, ftxt) == NULL)
	{
		printf("File Is Corrupted.\n");
	}
	else
	{
		//Reading the message from the given text file
		fgets(buffer, len, ftxt);
		
		//Encrypting the Message Length
		str_len = strlen(buffer);
		puts("String Length Encrypting");
		fseek(fsrc, seekpoint, SEEK_SET);
		bit_crypting(str_len, fdest, fsrc, seekpoint);	
		seekpoint = seekpoint + 32;
		
		fseek(fsrc, seekpoint, SEEK_SET);
		printf("String Encryption");
		
		for (i = 0; i < str_len; i++)
		{
			putchar('.');
			bit_char_crypting(buffer[i], fdest, fsrc, seekpoint);
			seekpoint = seekpoint + 8;
		}

	}


}

