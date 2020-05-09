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
            pixel[i][j].rgbtRed = .393 * pixel[i][j].rgbtRed + .769 * pixel[i][j].rgbtGreen + .189 * pixel[i][j].rgbtBlue;
            pixel[i][j].rgbtGreen = .349 * pixel[i][j].rgbtRed + .686 * pixel[i][j].rgbtGreen + .168 * pixel[i][j].rgbtBlue;
            pixel[i][j].rgbtBlue = .272 * pixel[i][j].rgbtRed + .534 * pixel[i][j].rgbtGreen + .131 * pixel[i][j].rgbtBlue;
        }
    }
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
