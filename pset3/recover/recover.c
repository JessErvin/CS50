#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2){
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // Set up our raw data
    char *raw_file = argv[1];

    // Open our file
    FILE *inptr = fopen(raw_file, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", raw_file);
        return 2;
    }

    // Set up the 512 byte buffer
    unsigned char *buffer = malloc(512);

    // Set up Variables
    int jpegsFound = 0;
    int fileNumber = 0;
    FILE *img;

    // Read blocks till end of file
    while (fread(buffer, 512, 1, inptr))
    {
        // If a new JPEG is found
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // close the previous JPEG
            if (jpegsFound > 0)
            {
                fclose(img);
            }

            // Create the filename
            char filename[7];
            sprintf(filename, "%03i.jpg", jpegsFound);

            // Open the JPEG
            img = fopen(filename, "w");

            // Increase JPEG count
            jpegsFound++;
        }

        // If a JPEG hasn't been found yet
        if (!jpegsFound)
        {
            continue;
        }

        //write JPEG info into current file
        fwrite(buffer, 512, 1, img);
    }

    // Close remaining files
    fclose(inptr);
    fclose(img);

    // Clear out memory
    free(buffer);

    return 0;
}
