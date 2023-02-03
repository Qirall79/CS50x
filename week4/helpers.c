#include "helpers.h"
#include <math.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int average = round((red + green + blue) / 3);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < round(width / 2); j++)
        {
            int currentPixelRed = image[i][j].rgbtRed;
            int currentPixelGreen = image[i][j].rgbtGreen;
            int currentPixelBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;

            image[i][width - j - 1].rgbtRed = currentPixelRed;
            image[i][width - j - 1].rgbtGreen = currentPixelGreen;
            image[i][width - j - 1].rgbtBlue = currentPixelBlue;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int red;
            int blue;
            int green;

            if(i - 1 < 0)
            {
                if(j - 1 < 0)
                {
                    RGBTRIPLE right = copy[i][j + 1];
                    RGBTRIPLE botRight = copy[i + 1][j + 1];
                    RGBTRIPLE bot = copy[i + 1][j];
                    RGBTRIPLE current = copy[i][j];

                    red = round((right.rgbtRed + botRight.rgbtRed + bot.rgbtRed + current.rgbtRed) /(float) 4);
                    green = round((right.rgbtGreen + botRight.rgbtGreen + bot.rgbtGreen + current.rgbtGreen) /(float) 4);
                    blue = round((right.rgbtBlue + botRight.rgbtBlue + bot.rgbtBlue + current.rgbtBlue) /(float) 4);
                }
                else if(j + 1 >= width)
                {
                    RGBTRIPLE left = copy[i][j - 1];
                    RGBTRIPLE botLeft = copy[i + 1][j - 1];
                    RGBTRIPLE bot = copy[i + 1][j];
                    RGBTRIPLE current = copy[i][j];

                    red = round((left.rgbtRed + botLeft.rgbtRed + bot.rgbtRed + current.rgbtRed) / (float) 4);
                    green = round((left.rgbtGreen + botLeft.rgbtGreen + bot.rgbtGreen + current.rgbtGreen) / (float) 4);
                    blue = round((left.rgbtBlue + botLeft.rgbtBlue + bot.rgbtBlue + current.rgbtBlue) / (float) 4);
                }
                else
                {
                    RGBTRIPLE right = copy[i][j + 1];
                    RGBTRIPLE left = copy[i][j - 1];
                    RGBTRIPLE botLeft = copy[i + 1][j - 1];
                    RGBTRIPLE bot = copy[i + 1][j];
                    RGBTRIPLE botRight = copy[i + 1][j + 1];
                    RGBTRIPLE current = copy[i][j];

                    red = round((right.rgbtRed + botRight.rgbtRed + bot.rgbtRed + left.rgbtRed + botLeft.rgbtRed + current.rgbtRed) / (float) 6);
                    green = round((right.rgbtGreen + botRight.rgbtGreen + bot.rgbtGreen + left.rgbtGreen + botLeft.rgbtGreen + current.rgbtGreen) / (float) 6);
                    blue = round((right.rgbtBlue + botRight.rgbtBlue + bot.rgbtBlue + left.rgbtBlue + botLeft.rgbtBlue + current.rgbtBlue) / (float) 6);
                }
            }
            else if(i + 1 >= height)
            {
                if(j - 1 < 0)
                {
                    RGBTRIPLE right = copy[i][j + 1];
                    RGBTRIPLE topRight = copy[i - 1][j + 1];
                    RGBTRIPLE top = copy[i - 1][j];
                    RGBTRIPLE current = copy[i][j];

                    red = round((right.rgbtRed + topRight.rgbtRed + top.rgbtRed + current.rgbtRed) / (float) 4);
                    green = round((right.rgbtGreen + topRight.rgbtGreen + top.rgbtGreen + current.rgbtGreen) / (float) 4);
                    blue = round((right.rgbtBlue + topRight.rgbtBlue + top.rgbtBlue + current.rgbtBlue) / (float) 4);

                }
                else if(j + 1 >= width)
                {
                    RGBTRIPLE left = copy[i][j - 1];
                    RGBTRIPLE topLeft = copy[i - 1][j - 1];
                    RGBTRIPLE top = copy[i - 1][j];
                    RGBTRIPLE current = copy[i][j];

                    red = round((left.rgbtRed + topLeft.rgbtRed + top.rgbtRed + current.rgbtRed) / (float) 4);
                    green = round((left.rgbtGreen + topLeft.rgbtGreen + top.rgbtGreen + current.rgbtGreen) / (float) 4);
                    blue = round((left.rgbtBlue + topLeft.rgbtBlue + top.rgbtBlue + current.rgbtBlue) / (float) 4);
                }
                else
                {
                    RGBTRIPLE right = copy[i][j + 1];
                    RGBTRIPLE left = copy[i][j - 1];
                    RGBTRIPLE topLeft = copy[i - 1][j - 1];
                    RGBTRIPLE top = copy[i - 1][j];
                    RGBTRIPLE topRight = copy[i - 1][j + 1];
                    RGBTRIPLE current = copy[i][j];

                    red = round((left.rgbtRed + topLeft.rgbtRed + top.rgbtRed + right.rgbtRed + topRight.rgbtRed + current.rgbtRed) / (float) 6);
                    green = round((left.rgbtGreen + topLeft.rgbtGreen + top.rgbtGreen + right.rgbtGreen + topRight.rgbtGreen + current.rgbtGreen) / (float) 6);
                    blue = round((left.rgbtBlue + topLeft.rgbtBlue + top.rgbtBlue + right.rgbtBlue + topRight.rgbtBlue + current.rgbtBlue) / (float) 6);
                }
            }

            else if (j - 1 < 0)
            {
                RGBTRIPLE right = copy[i][j + 1];
                RGBTRIPLE top = copy[i - 1][j];
                RGBTRIPLE topRight = copy[i - 1][j + 1];
                RGBTRIPLE bot = copy[i + 1][j];
                RGBTRIPLE botRight = copy[i + 1][j + 1];
                RGBTRIPLE current = copy[i][j];

                red = round((right.rgbtRed + botRight.rgbtRed + bot.rgbtRed + top.rgbtRed + topRight.rgbtRed + current.rgbtRed) / (float) 6);
                green = round((right.rgbtGreen + botRight.rgbtGreen + bot.rgbtGreen + top.rgbtGreen + topRight.rgbtGreen + current.rgbtGreen) / (float) 6);
                blue = round((right.rgbtBlue + botRight.rgbtBlue + bot.rgbtBlue + top.rgbtBlue + topRight.rgbtBlue + current.rgbtBlue) / (float) 6);
            }
            else if(j + 1 >= width)
            {
                RGBTRIPLE left = copy[i][j - 1];
                RGBTRIPLE top = copy[i - 1][j];
                RGBTRIPLE topLeft = copy[i - 1][j - 1];
                RGBTRIPLE bot = copy[i + 1][j];
                RGBTRIPLE botLeft = copy[i + 1][j - 1];
                RGBTRIPLE current = copy[i][j];

                red = round((left.rgbtRed + botLeft.rgbtRed + bot.rgbtRed + top.rgbtRed + topLeft.rgbtRed + current.rgbtRed) / (float) 6);
                green = round((left.rgbtGreen + botLeft.rgbtGreen + bot.rgbtGreen + top.rgbtGreen + topLeft.rgbtGreen + current.rgbtGreen) / (float) 6);
                blue = round((left.rgbtBlue + botLeft.rgbtBlue + bot.rgbtBlue + top.rgbtBlue + topLeft.rgbtBlue + current.rgbtBlue) / (float) 6);
            }
            else
            {
                RGBTRIPLE left = copy[i][j - 1];
                RGBTRIPLE top = copy[i - 1][j];
                RGBTRIPLE topLeft = copy[i - 1][j - 1];
                RGBTRIPLE bot = copy[i + 1][j];
                RGBTRIPLE botLeft = copy[i + 1][j - 1];
                RGBTRIPLE right = copy[i][j + 1];
                RGBTRIPLE topRight = copy[i - 1][j + 1];
                RGBTRIPLE botRight = copy[i + 1][j + 1];
                RGBTRIPLE current = copy[i][j];

                red = round((left.rgbtRed + botLeft.rgbtRed + bot.rgbtRed + top.rgbtRed + topLeft.rgbtRed + right.rgbtRed + botRight.rgbtRed + topRight.rgbtRed + current.rgbtRed) / (float) 9);
                green = round((right.rgbtGreen + botRight.rgbtGreen + left.rgbtGreen + botLeft.rgbtGreen + bot.rgbtGreen + top.rgbtGreen + topLeft.rgbtGreen + topRight.rgbtGreen + current.rgbtGreen) / (float) 9);
                blue = round((right.rgbtBlue + botRight.rgbtBlue + left.rgbtBlue + botLeft.rgbtBlue + bot.rgbtBlue + top.rgbtBlue + topLeft.rgbtBlue + topRight.rgbtBlue + current.rgbtBlue) / (float) 9);
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;

        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    int gxFactor[9];

    gxFactor[0] = -1;
    gxFactor[1] = 0;
    gxFactor[2] = 1;
    gxFactor[3] = -2;
    gxFactor[4] = 0;
    gxFactor[5] = 2;
    gxFactor[6] = -1;
    gxFactor[7] = 0;
    gxFactor[8] = 1;

    int gyFactor[9];

    gyFactor[0] = -1;
    gyFactor[1] = -2;
    gyFactor[2] = -1;
    gyFactor[3] = 0;
    gyFactor[4] = 0;
    gyFactor[5] = 0;
    gyFactor[6] = 1;
    gyFactor[7] = 2;
    gyFactor[8] = 1;

    RGBTRIPLE left;
    RGBTRIPLE top;
    RGBTRIPLE topLeft;
    RGBTRIPLE bot;
    RGBTRIPLE botLeft;
    RGBTRIPLE right;
    RGBTRIPLE topRight;
    RGBTRIPLE botRight;
    RGBTRIPLE current;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {


            if(i - 1 < 0)
            {
                if(j - 1 < 0)
                {

                    left.rgbtRed = 0; left.rgbtGreen = 0; left.rgbtBlue = 0;
                    top.rgbtRed = 0; top.rgbtGreen = 0; top.rgbtBlue = 0;
                    topLeft.rgbtRed = 0; topLeft.rgbtGreen = 0; topLeft.rgbtBlue = 0;
                    topRight.rgbtRed = 0; topRight.rgbtGreen = 0; topRight.rgbtBlue = 0;
                    botLeft.rgbtRed = 0; botLeft.rgbtGreen = 0; botLeft.rgbtBlue = 0;

                    right = copy[i][j + 1];
                    botRight = copy[i + 1][j + 1];
                    bot = copy[i + 1][j];
                    current = copy[i][j];

                }
                else if(j + 1 >= width)
                {

                    right.rgbtRed = 0; right.rgbtGreen = 0; right.rgbtBlue = 0;
                    top.rgbtRed = 0; top.rgbtGreen = 0; top.rgbtBlue = 0;
                    topLeft.rgbtRed = 0; topLeft.rgbtGreen = 0; topLeft.rgbtBlue = 0;
                    topRight.rgbtRed = 0; topRight.rgbtGreen = 0; topRight.rgbtBlue = 0;
                    botRight.rgbtRed = 0; botRight.rgbtGreen = 0; botRight.rgbtBlue = 0;

                    left = copy[i][j - 1];
                    botLeft = copy[i + 1][j - 1];
                    bot = copy[i + 1][j];
                    current = copy[i][j];

                }
                else
                {
                    top.rgbtRed = 0; top.rgbtGreen = 0; top.rgbtBlue = 0;
                    topLeft.rgbtRed = 0; topLeft.rgbtGreen = 0; topLeft.rgbtBlue = 0;
                    topRight.rgbtRed = 0; topRight.rgbtGreen = 0; topRight.rgbtBlue = 0;

                    right = copy[i][j + 1];
                    left = copy[i][j - 1];
                    botLeft = copy[i + 1][j - 1];
                    bot = copy[i + 1][j];
                    botRight = copy[i + 1][j + 1];
                    current = copy[i][j];

                }
            }
            else if(i + 1 >= height)
            {
                if(j - 1 < 0)
                {
                    topLeft.rgbtRed = 0; topLeft.rgbtGreen = 0; topLeft.rgbtBlue = 0;
                    botRight.rgbtRed = 0; botRight.rgbtGreen = 0; botRight.rgbtBlue = 0;
                    botLeft.rgbtRed = 0; botLeft.rgbtGreen = 0; botLeft.rgbtBlue = 0;
                    left.rgbtRed = 0; left.rgbtGreen = 0; left.rgbtBlue = 0;
                    bot.rgbtRed = 0; bot.rgbtGreen = 0; bot.rgbtBlue = 0;

                    right = copy[i][j + 1];
                    topRight = copy[i - 1][j + 1];
                    top = copy[i - 1][j];
                    current = copy[i][j];

                }
                else if(j + 1 >= width)
                {
                    botRight.rgbtRed = 0; botRight.rgbtGreen = 0; botRight.rgbtBlue = 0;
                    botLeft.rgbtRed = 0; botLeft.rgbtGreen = 0; botLeft.rgbtBlue = 0;
                    bot.rgbtRed = 0; bot.rgbtGreen = 0; bot.rgbtBlue = 0;
                    right.rgbtRed = 0; right.rgbtGreen = 0; right.rgbtBlue = 0;
                    topRight.rgbtRed = 0; topRight.rgbtGreen = 0; topRight.rgbtBlue = 0;

                    left = copy[i][j - 1];
                    topLeft = copy[i - 1][j - 1];
                    top = copy[i - 1][j];
                    current = copy[i][j];

                }
                else
                {
                    botRight.rgbtRed = 0; botRight.rgbtGreen = 0; botRight.rgbtBlue = 0;
                    botLeft.rgbtRed = 0; botLeft.rgbtGreen = 0; botLeft.rgbtBlue = 0;
                    bot.rgbtRed = 0; bot.rgbtGreen = 0; bot.rgbtBlue = 0;

                    right = copy[i][j + 1];
                    left = copy[i][j - 1];
                    topLeft = copy[i - 1][j - 1];
                    top = copy[i - 1][j];
                    topRight = copy[i - 1][j + 1];
                    current = copy[i][j];

                }
            }

            else if (j - 1 < 0)
            {
                botLeft.rgbtRed = 0; botLeft.rgbtGreen = 0; botLeft.rgbtBlue = 0;
                left.rgbtRed = 0; left.rgbtGreen = 0; left.rgbtBlue = 0;
                topLeft.rgbtRed = 0; topLeft.rgbtGreen = 0; topLeft.rgbtBlue = 0;

                right = copy[i][j + 1];
                top = copy[i - 1][j];
                topRight = copy[i - 1][j + 1];
                bot = copy[i + 1][j];
                botRight = copy[i + 1][j + 1];
                current = copy[i][j];

            }
            else if(j + 1 >= width)
            {
                right.rgbtRed = 0; right.rgbtGreen = 0; right.rgbtBlue = 0;
                topRight.rgbtRed = 0; topRight.rgbtGreen = 0; topRight.rgbtBlue = 0;
                botRight.rgbtRed = 0; botRight.rgbtGreen = 0; botRight.rgbtBlue = 0;

                left = copy[i][j - 1];
                top = copy[i - 1][j];
                topLeft = copy[i - 1][j - 1];
                bot = copy[i + 1][j];
                botLeft = copy[i + 1][j - 1];
                current = copy[i][j];

            }
            else
            {
                left = copy[i][j - 1];
                top = copy[i - 1][j];
                topLeft = copy[i - 1][j - 1];
                bot = copy[i + 1][j];
                botLeft = copy[i + 1][j - 1];
                right = copy[i][j + 1];
                topRight = copy[i - 1][j + 1];
                botRight = copy[i + 1][j + 1];
                current = copy[i][j];

            }

            RGBTRIPLE arround[9];

            arround[0] = topLeft;
            arround[1] = top;
            arround[2] = topRight;
            arround[3] = left;
            arround[4] = current;
            arround[5] = right;
            arround[6] = botLeft;
            arround[7] = bot;
            arround[8] = botRight;

            int gxRed = 0;
            int gyRed = 0;
            int gyGreen = 0;
            int gxGreen = 0;
            int gyBlue = 0;
            int gxBlue = 0;

            for(int k = 0; k < 9; k++)
            {
                gxRed += arround[k].rgbtRed * gxFactor[k];
                gxGreen += arround[k].rgbtGreen * gxFactor[k];
                gxBlue += arround[k].rgbtBlue * gxFactor[k];

                gyRed += arround[k].rgbtRed * gyFactor[k];
                gyGreen += arround[k].rgbtGreen * gyFactor[k];
                gyBlue += arround[k].rgbtBlue * gyFactor[k];
            }

            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));

            if(red > 255)
            {
                red = 255;
            }
            if(green > 255)
            {
                green = 255;
            }
            if(blue > 255)
            {
                blue = 255;
            }

            if(red != 0)
            {
                image[i][j].rgbtRed = red;
            }
            if(green != 0)
            {
                image[i][j].rgbtGreen = green;
            }
            if(blue != 0)
            {
                image[i][j].rgbtBlue = blue;
            }




        }
    }
    return;
}
