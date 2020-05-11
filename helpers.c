#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE pixels[height][width])
{
    for (int i = 0; i < height; i++)//Browse the pixel matrix
    {
        for (int j = 0; j < width; j++)
        {
            BYTE average = round((float)(pixels[i][j].rgbtRed + pixels[i][j].rgbtGreen + pixels[i][j].rgbtBlue) / 3);
            pixels[i][j].rgbtRed = average;
            pixels[i][j].rgbtGreen = average;
            pixels[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE pixels[height][width])
{
    for (int i = 0; i < height; i++)//Browse the pixel matrix
    {
        for (int j = 0; j < width; j++)
        {
            BYTE originalRed = pixels[i][j].rgbtRed;
            BYTE originalGreen = pixels[i][j].rgbtGreen;
            BYTE originalBlue = pixels[i][j].rgbtBlue;
            BYTE sepiaRed = 0;
            BYTE sepiaBlue = 0;
            BYTE sepiaGreen = 0;
            //Checks if the value does not exceed the max value of one byte
            if (round((float)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue)) > 255)
            {
                sepiaRed = 255;
            }
            else
            {
                sepiaRed = round((float)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            }
            //Checks if the value does not exceed the max value of one byte
            if (round((float)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue)) > 255)
            {
                sepiaGreen = 255;
            }
            else
            {
                sepiaGreen = round((float)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            }
            //Checks if the value does not exceed the max value of one byte
            if (round((float)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue)) > 255)
            {
                sepiaBlue = 255;
            }
            else
            {
                sepiaBlue = round((float)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));
            }
            pixels[i][j].rgbtRed = sepiaRed;
            pixels[i][j].rgbtBlue = sepiaBlue;
            pixels[i][j].rgbtGreen = sepiaGreen;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE pixels[height][width])
{
    for (int i = 0; i < height; i++)//Browse the pixel matrix
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE temp = pixels[i][j];
            pixels[i][j] = pixels[i][width - 1 - j];
            pixels[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE pixels[height][width])
{
    int h = height;
    int w = width;
    RGBTRIPLE copy[h][w];
    //Copy pixels into "copy"
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            copy[i][j] = pixels[i][j];
        }
    }
    for (int i = 0; i < h; i++)//Browse the pixel matrix
    {
        for (int j = 0; j < w; j++)
        {
            float Red = 0;
            float Green = 0;
            float Blue = 0;
            int count = 0;
            for (int a = -1; a < 2; a++)//Look at the contiguous pixels
            {
                for (int s = -1; s < 2; s++)
                {
                    int x = i + a;
                    int y = j + s;
                    if (x < 0 || y < 0 || x == h || y == w) //If it's an edge or a corner avoids indexes out of the bound
                    {
                        continue;
                    }
                    Red += pixels[x][y].rgbtRed;
                    Green += pixels[x][y].rgbtGreen;
                    Blue += pixels[x][y].rgbtBlue;
                    count++;
                }
            }
            //Compute rgb values of contiguous pixels
            float RedAverage = round(Red / count);
            float GreenAverage = round(Green / count);
            float BlueAverage = round(Blue / count);
            //Assign them to our "copy" pixel matrix
            copy[i][j].rgbtRed = RedAverage;
            copy[i][j].rgbtGreen = GreenAverage;
            copy[i][j].rgbtBlue = BlueAverage;
        }
    }
    //Assigns our pixel matrix the "copy" values
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            pixels[i][j] = copy[i][j];
        }
    }
    return;
}