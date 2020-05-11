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
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = pixel[i][j];
            pixel[i][j] = pixel[i][width-1-j];
            pixel[i][width-1-j] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE pixel[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            RGBTRIPLE average;
           if (i == 0 && j != 0 && j != width-1)//top
            {
                average.rgbtRed = round((float)(pixel[i][j-1].rgbtRed+pixel[i][j].rgbtRed+pixel[i][j+1].rgbtRed+pixel[i+1][j-1].rgbtRed+pixel[i+1][j].rgbtRed+pixel[i+1][j+1].rgbtRed)/6);
                average.rgbtGreen = round((float)(pixel[i][j-1].rgbtGreen+pixel[i][j].rgbtGreen+pixel[i][j+1].rgbtGreen+pixel[i+1][j-1].rgbtGreen+pixel[i+1][j].rgbtGreen+pixel[i+1][j+1].rgbtGreen)/6);
                average.rgbtBlue = round((float)(pixel[i][j-1].rgbtBlue+pixel[i][j].rgbtBlue+pixel[i][j+1].rgbtBlue+pixel[i+1][j-1].rgbtBlue+pixel[i+1][j].rgbtBlue+pixel[i+1][j+1].rgbtBlue)/6);
                temp[i][j]     = average;
                continue; 
            }
            else if (i == height-1 && j != 0 && j != width-1)//bot
            {
                average.rgbtRed = round((float)(pixel[i-1][j-1].rgbtRed+pixel[i-1][j].rgbtRed+pixel[i-1][j+1].rgbtRed+pixel[i][j-1].rgbtRed+pixel[i][j].rgbtRed+pixel[i][j+1].rgbtRed)/6);
                average.rgbtGreen = round((float)(pixel[i-1][j-1].rgbtGreen+pixel[i-1][j].rgbtGreen+pixel[i-1][j+1].rgbtGreen+pixel[i][j-1].rgbtGreen+pixel[i][j].rgbtGreen+pixel[i][j+1].rgbtGreen)/6);
                average.rgbtBlue = round((float)(pixel[i-1][j-1].rgbtBlue+pixel[i-1][j].rgbtBlue+pixel[i-1][j+1].rgbtBlue+pixel[i][j-1].rgbtBlue+pixel[i][j].rgbtBlue+pixel[i][j+1].rgbtBlue)/6);
                temp[i][j]     = average;
                continue;    
            }
            else if (i != 0 && i != height-1 && j == 0)//left
            {
                average.rgbtRed = round((float)(pixel[i-1][j].rgbtRed+pixel[i-1][j+1].rgbtRed+pixel[i][j].rgbtRed+pixel[i][j+1].rgbtRed+pixel[i+1][j].rgbtRed+pixel[i+1][j+1].rgbtRed)/6);
                average.rgbtGreen = round((float)(pixel[i-1][j].rgbtGreen+pixel[i-1][j+1].rgbtGreen+pixel[i][j].rgbtGreen+pixel[i][j+1].rgbtGreen+pixel[i+1][j].rgbtGreen+pixel[i+1][j+1].rgbtGreen)/6);
                average.rgbtBlue = round((float)(pixel[i-1][j].rgbtBlue+pixel[i-1][j+1].rgbtBlue+pixel[i][j].rgbtBlue+pixel[i][j+1].rgbtBlue+pixel[i+1][j].rgbtBlue+pixel[i+1][j+1].rgbtBlue)/6);
                temp[i][j]     = average;
                continue;
            }
            else if (i != 0 && i != height-1 && j == width-1)//rigth
            {
                average.rgbtRed = round((float)(pixel[i-1][j-1].rgbtRed+pixel[i-1][j].rgbtRed+pixel[i][j-1].rgbtRed+pixel[i][j].rgbtRed+pixel[i+1][j-1].rgbtRed+pixel[i+1][j].rgbtRed)/6);
                average.rgbtGreen = round((float)(pixel[i-1][j-1].rgbtGreen+pixel[i-1][j].rgbtGreen+pixel[i][j-1].rgbtGreen+pixel[i][j].rgbtGreen+pixel[i+1][j-1].rgbtGreen+pixel[i+1][j].rgbtGreen)/6);
                average.rgbtBlue = round((float)(pixel[i-1][j-1].rgbtBlue+pixel[i-1][j].rgbtBlue+pixel[i][j-1].rgbtBlue+pixel[i][j].rgbtBlue+pixel[i+1][j-1].rgbtBlue+pixel[i+1][j].rgbtBlue)/6);
                temp[i][j]     = average;
                continue;
            }
            else
            {
                average.rgbtRed = round((float)(pixel[i-1][j-1].rgbtRed+pixel[i-1][j].rgbtRed+pixel[i-1][j+1].rgbtRed+pixel[i][j-1].rgbtRed+pixel[i][j].rgbtRed+pixel[i][j+1].rgbtRed+pixel[i+1][j-1].rgbtRed+pixel[i+1][j].rgbtRed+pixel[i+1][j+1].rgbtRed)/9);
                average.rgbtGreen = round((float)(pixel[i-1][j-1].rgbtGreen+pixel[i-1][j].rgbtGreen+pixel[i-1][j+1].rgbtGreen+pixel[i][j-1].rgbtGreen+pixel[i][j].rgbtGreen+pixel[i][j+1].rgbtGreen+pixel[i+1][j-1].rgbtGreen+pixel[i+1][j].rgbtGreen+pixel[i+1][j+1].rgbtGreen)/9);
                average.rgbtBlue = round((float)(pixel[i-1][j-1].rgbtBlue+pixel[i-1][j].rgbtBlue+pixel[i-1][j+1].rgbtBlue+pixel[i][j-1].rgbtBlue+pixel[i][j].rgbtBlue+pixel[i][j+1].rgbtBlue+pixel[i+1][j-1].rgbtBlue+pixel[i+1][j].rgbtBlue+pixel[i+1][j+1].rgbtBlue)/9);
                temp[i][j]     = average;
                continue;
            }
            //corner detection
        }
    }
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            pixel[i][j] = temp[i][j];
        }
    }
    return;
}
