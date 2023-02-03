#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

FILE *img;

int main(int argc, char *argv[])
{
    //making sure the arguments are correct
    if(argc != 2)
    {
        printf("Usage: ./recover image\n");

        return 1;
    }


    FILE *f = fopen(argv[1], "r");

    //making sure there is actually content in the file
    if(f == NULL)
    {
        fclose(f);

        return 1;
    }

    BYTE buffer[512];

    int fileCount = 0;

    //reading 512 bytes to buffer until the end of the file
    while(fread(&buffer, sizeof(BYTE), 512, f) == 512)
    {

        //allocating enough memory for the filename string
        char *filename = malloc(8 * sizeof(BYTE));

        //checking if it's the header of a jpeg file
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //composing the filename ###.jpg
            sprintf(filename, "%03i.jpg", fileCount);

            //checking if it's the first jpeg file found
            if(fileCount == 0)
            {
                img = fopen(filename, "w");

                fwrite(&buffer, sizeof(BYTE), 512, img);

            }

            else
            {
                fclose(img);

                img = fopen(filename, "w");

                fwrite(&buffer, sizeof(BYTE), 512, img);
            }

            fileCount++;

        }

        //in case it's not the start of a jpeg we gonna continue writing
        else
        {
            if(fileCount > 0)
            {
                fwrite(&buffer, sizeof(BYTE), 512, img);
            }
        }
    }
}