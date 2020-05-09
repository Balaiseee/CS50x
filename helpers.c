#include "helpers.h"
#include <math.h>

RGBTRIPLE average(RGBTRIPLE pixel)
{
    BYTE average = round((pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3);
    RGBTRIPLE result;
    result.rgbtRed = average;
    result.rgbtGreen = average;
    result.rgbtBlue = average;
    return result;
}
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE pixel[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            pixel[i][j] = average(pixel[i][j]);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
