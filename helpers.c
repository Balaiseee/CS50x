#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE pixel[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            BYTE average = round((float)(pixel[i][j].rgbtRed + pixel[i][j].rgbtGreen + pixel[i][j].rgbtBlue) / 3);
            pixel[i][j].rgbtRed = average;
            pixel[i][j].rgbtGreen = average;
            pixel[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE pixel[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            BYTE originalRed = pixel[i][j].rgbtRed;
            BYTE originalGreen = pixel[i][j].rgbtGreen;
            BYTE originalBlue = pixel[i][j].rgbtBlue;
            BYTE sepiaRed = 0;
            BYTE sepiaBlue = 0;
            BYTE sepiaGreen = 0;
            if (round((float)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue)) > 255)
            {
                sepiaRed = 255;
            }
            else
            {
                sepiaRed = round((float)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            }
            if (round((float)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue)) > 255)
            {
                sepiaGreen = 255;
            }
            else
            {
                sepiaGreen = round((float)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            }
            if (round((float)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue)) > 255)
            {
                sepiaBlue = 255;
            }
            else
            {
                sepiaBlue = round((float)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));
            }
            pixel[i][j].rgbtRed = sepiaRed;
            pixel[i][j].rgbtBlue = sepiaBlue;
            pixel[i][j].rgbtGreen = sepiaGreen;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE pixel[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2+1; j++)
        {
            RGBTRIPLE temp = pixel[i][j];
            pixel[i][j] = pixel[i][width-1-j];
            pixel[i][width-1-j] = temp;
            
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
