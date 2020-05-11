#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE pixels[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
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
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            BYTE originalRed = pixels[i][j].rgbtRed;
            BYTE originalGreen = pixels[i][j].rgbtGreen;
            BYTE originalBlue = pixels[i][j].rgbtBlue;
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
            pixels[i][j].rgbtRed = sepiaRed;
            pixels[i][j].rgbtBlue = sepiaBlue;
            pixels[i][j].rgbtGreen = sepiaGreen;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE pixels[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE temp = pixels[i][j];
            pixels[i][j] = pixels[i][width-1-j];
            pixels[i][width-1-j] = temp;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE pixels[height][width])
{
    int h = height;
    int w = width;
    RGBTRIPLE copyimage[height][width];
    // copy image
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            copyimage[i][j] = pixels[i][j];
        }
    }

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            float Red = 0;
            float Green = 0;
            float Blue = 0;
            int count = 0;

            for (int a = -1; a < 2; a++) //Look at the contiguous pixelss
            {
                for (int s = -1; s < 2; s++)
                {
                    int x = i + a;
                    int y = j + s;

                    if (x < 0 || y < 0 || x == h || y == w)
                    {
                        continue;
                    }

                    Red += pixels[x][y].rgbtRed;
                    Green += pixels[x][y].rgbtGreen;
                    Blue += pixels[x][y].rgbtBlue;
                    count++;
                }
            }
            
            float RedAverage = round(Red / count);
            float GreenAverage = round(Green / count);
            float BlueAverage = round(Blue / count);

            copyimage[i][j].rgbtRed = RedAverage;
            copyimage[i][j].rgbtGreen = GreenAverage;
            copyimage[i][j].rgbtBlue = BlueAverage;

        }
    }

    for (int i = 0; i < h; i++) // loop through rows
    {
        for (int j = 0; j < w; j++) // loop throug colums within the row
        {
            pixels[i][j] = copyimage[i][j];
        }
    }

    return;
}