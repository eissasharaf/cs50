#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // validate the input data
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    //open the input file
    FILE *f = fopen(argv[1], "r");
    //validate the input file
    if (f == NULL)
    {
        printf("can't open %s\n", argv[1]);
        return 1;

    }
    FILE *img = NULL;
    int count = 0;
    BYTE data[512];
    char out[20];
    while (fread(data, sizeof(BYTE), 512, f) == 512)//read 512 byte from the card
    {
        if (data[0] == 0xff && data[1] == 0xd8 && data[2] == 0xff && (data[3] & 0xf0) == 0xe0)// check for the beginning of new jpg file
        {
            if (count != 0)// close the previous file if there is
            {
                fclose(img);
            }
            //create new jpg file
            sprintf(out, "%03i.jpg", count);
            img = fopen(out, "w");
            if (img == NULL)
            {
                printf("error");
                return 1;
            }
            count++;
        }
        if (count != 0)
        {
            //write to the created file
            fwrite(data, sizeof(BYTE), 512, img);

        }
    }
    //end of the card
    //close all allocated memory
    fclose(img);
    fclose(f);
}
