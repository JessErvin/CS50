// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    // ADD A 3RD VARIABLE (N)
    if (argc != 4 || atof(argv[1]) > 100 || atof(argv[1]) < 0)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // remember filenames
    // CHANGE FILE NAMES AND ADD ONE FOR N
    char *infile = argv[2];
    char *outfile = argv[3];
    float n = atof(argv[1]);

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
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

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
    int outputWidth = floor(inputWidth * n);
    int outputHeight = floor(inputHeight * n);

    // determine padding for scanlines
    int inputPadding = (4 - (inputWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int outputPadding = (4 - (outputWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // NEW HEADERS:
    bi.biWidth = outputWidth;
    bi.biHeight = outputHeight;
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * outputWidth) + outputPadding) * abs(outputHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // GET RATIO
    double widthRatio = (double) inputWidth / (double) outputWidth;
    double heightRatio = (double) inputHeight / (double) outputHeight;

    // STORE A SCANLINE TO MEMORY
    RGBTRIPLE scanline[inputWidth * sizeof(RGBTRIPLE)];
    int cachedScanline = -1;


    // iterate over infile's scanlines

    for (int i = 0, biHeight = abs(outputHeight); i < biHeight; i++)
    {
        int row = i * heightRatio;

        if (cachedScanline != row)
        {
            fseek(inptr, sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (((sizeof(RGBTRIPLE) * inputWidth) + inputPadding) * row),
                  SEEK_SET);
            fread(scanline, sizeof(RGBTRIPLE), inputWidth, inptr);
            cachedScanline = row;
        }



        // iterate over pixels in scanline
        for (int j = 0; j < outputWidth; j++)
        {
            // skip over padding, if any
            fseek(inptr, inputPadding, SEEK_CUR);

            int column = j * widthRatio;
            fwrite(&scanline[column], sizeof(RGBTRIPLE), 1, outptr);
        }

        // WRITE THE NEW PADDING
        for (int k = 0; k < outputPadding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
