// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    // ADD A 3RD VARIABLE (N)
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    // CHANGE FILE NAMES AND ADD ONE FOR N
    char *infile = argv[2];
    char *outfile = argv[3];
    int n = atoi(argv[1]);

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfo;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfo = bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi, bio;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    bio = bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // NEW OUTPUT DIMENSIONS
    int inputWidth = bi.biWidth;
    int inputHeight = bi.biHeight;
    int outputWidth = inputWidth * n;
    int outputHeight = inputHeight * n;

    // determine padding for scanlines
    int inputPadding = (4 - (inputWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // NEW PADDING
    int outputPadding = (4 - (outputWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // NEW HEADERS:
    bio.biWidth = outputWidth;
    bio.biHeight = outputHeight;
    bio.biSizeImage = ((sizeof(RGBTRIPLE) * outputWidth) + outputPadding) * abs(outputHeight);
    bfo.bfSize = bio.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bfo, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bio, sizeof(BITMAPINFOHEADER), 1, outptr);

    // STORE A SCANLINE TO REPEAT N TIMES
    RGBTRIPLE scanline[outputWidth * sizeof(RGBTRIPLE)];


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inputHeight); i < biHeight; i++)
    {
        // temporary storage
        RGBTRIPLE triple;

        // iterate over pixels in scanline
        for (int j = 0; j < inputWidth; j++)
        {

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // SETUP THE TEMP SCANLINE
            for (int k = 0; k < n; k ++)
            {
                scanline[(j * n) + k] = triple;
            }
        }

        // skip over padding, if any
        fseek(inptr, inputPadding, SEEK_CUR);

        // WRITE THE SCANLINE N TIMES
        for (int l = 0; l < n; l++)
        {
            // WRITE THE SCANLINE
            fwrite(&scanline, sizeof(RGBTRIPLE) * outputWidth, 1, outptr);

            // WRITE THE NEW PADDING
            for (int m = 0; m < outputPadding; m++)
            {
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
