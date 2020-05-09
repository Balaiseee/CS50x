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
            BYTE originalRed = round((float)(pixel[i][j].rgbtRed));
            BYTE originalGreen = round((float)(pixel[i][j].rgbtGreen));
            BYTE originalBlue = round((float)(pixel[i][j].rgbtBlue));
            pixel[i][j].rgbtRed = round((float)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
            pixel[i][j].rgbtGreen = round((float)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
            pixel[i][j].rgbtBlue = round((float)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));
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
