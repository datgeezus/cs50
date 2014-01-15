/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>

#define BLOCK 512

const char* rawName = "card.raw";           // Name of raw file
int imageIndex = 0;                         // n images found
unsigned char buffer[BLOCK];                          // temporary buffer
const unsigned char jpeg[] = {0xFF, 0xD8, 0xFF, 0xE0, 0xE1};// starting byte secuence of JPEGs
                            // States for state machine


void writeImage(int index);
int findNewImage();

int main(int argc, char* argv[])
{
    if (argc != 1)
    {
        printf("Usage: %s\n", argv[0]);
        return 1;
    }

    FILE* rawFile = fopen(rawName,"r");
    if (rawFile == NULL)
    {
        printf("Could not open %s.\n", rawName);
        return 2;
    }

    int firstImageFound = 0;
    while( fread(&buffer, BLOCK, 1, rawFile) == 1)
    {
        if (firstImageFound == 1)
        {
            if (findNewImage() == 1)
                imageIndex++;
            writeImage(imageIndex);
        }
        else if (findNewImage() == 1)
        {
            firstImageFound = 1;
            writeImage(imageIndex);
        }
    }
    fclose(rawFile);
}

int findNewImage()
{
    if (buffer[0] == jpeg[0])
    {
        if (buffer[1] == jpeg[1])
        {
            if (buffer[2] == jpeg[2])
            {
                if (buffer[3] == jpeg[3] || buffer[3] == jpeg[4])
                {
                    return 1;
                }
            }
        }
    }

    return 0;
}

void writeImage(int index)
{
    char name[7];
    sprintf(name, "%.3i.jpg", index);

    FILE* image = fopen(name,"a");
    if (image == NULL)
        return;
    fwrite(&buffer, BLOCK, 1, image);
    fclose(image);
}

