#include "helpers.h"

BYTE average(RGBTRIPLE pixel)
{
    return (pixel.rgbtRed + pixel.rgbtGreen + pixel.rgbtBlue) / 3;
}
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE pixel[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            pixel[i][j].rgbtRed = average(pixel[i][j]);
            pixel[i][j].rgbtGreen = average(pixel[i][j]);
            pixel[i][j].rgbtBlue = average(pixel[i][j]);
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
