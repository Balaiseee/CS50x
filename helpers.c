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
            BYTE sepiaRed = (int)(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            BYTE sepiaGreen = (int)(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            BYTE sepiaBlue = (int)(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);
            if (sepiaRed > 255)
            {
                pixel[i][j].rgbtRed = 255;
            }
            else
            {
                pixel[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaGreen > 255)
            {
                pixel[i][j].rgbtGreen = 255;
            }
            else
            {
                pixel[i][j].rgbtGreen = sepiaGreen;
            }
            if (sepiaBlue > 255)
            {
                pixel[i][j].rgbtBlue = 255;
            }
            else
            {
                pixel[i][j].rgbtBlue = sepiaBlue;
            }
            
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
