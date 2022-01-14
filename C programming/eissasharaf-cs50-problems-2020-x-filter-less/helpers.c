#include "helpers.h"
#include <math.h>
#include<stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = round((image[i][j].rgbtRed + image[i][j].rgbtGreen +
                                  image[i][j].rgbtBlue) / 3.0);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red, green, blue;
            red =  .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            green = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            blue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = round(red);
            }

            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = round(green);
            }

            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = round(blue);
            }

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float red, green, blue;
    int count;
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            red =  image[i][j].rgbtRed;
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            count = 1;
            if (j != 0)
            {
                red += image[i][j - 1].rgbtRed; 
                blue += image[i][j - 1].rgbtBlue;
                green += image[i][j - 1].rgbtGreen;
                count++;
            }
            if (j != width - 1)
            {
                red +=  image[i][j + 1].rgbtRed;
                blue += image[i][j + 1].rgbtBlue;
                green += image[i][j + 1].rgbtGreen;
                count++;
            }
            if (i != 0)
            {
                red += image[i - 1][j].rgbtRed;
                blue += image[i - 1][j].rgbtBlue;
                green += image[i - 1][j].rgbtGreen;
                count++;
                if (j != 0)
                {
                    red +=  image[i - 1][j - 1].rgbtRed;
                    blue += image[i - 1][j - 1].rgbtBlue;
                    green += image[i - 1][j - 1].rgbtGreen;
                    count++;
                }
                if (j != width - 1)
                {
                    red +=  image[i - 1][j + 1].rgbtRed;
                    blue += image[i - 1][j + 1].rgbtBlue;
                    green += image[i - 1][j + 1].rgbtGreen;
                    count++;
                }
            }
            if (i != height - 1)
            {
                red += image[i + 1][j].rgbtRed;
                blue += image[i + 1][j].rgbtBlue;
                green += image[i + 1][j].rgbtGreen;
                count++;
                if (j != 0)
                {
                    red +=  image[i + 1][j - 1].rgbtRed;
                    blue += image[i + 1][j - 1].rgbtBlue;
                    green += image[i + 1][j - 1].rgbtGreen;
                    count++;
                }
                if (j != width - 1)
                {
                    red +=  image[i + 1][j + 1].rgbtRed;
                    blue += image[i + 1][j + 1].rgbtBlue;
                    green += image[i + 1][j + 1].rgbtGreen;
                    count++;
                }
            }
            copy[i][j].rgbtRed = round(red / count);
            copy[i][j].rgbtBlue = round(blue / count);
            copy[i][j].rgbtGreen = round(green / count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
        }

    }

    return;
}
