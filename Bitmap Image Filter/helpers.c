#include "helpers.h"
#include <math.h>
#include <stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float r ;
    float g ;
    float b ;
    float av;
    float avgreen ;
    float avblue ;
    int average ;
    // loop around the image to get average of red green and blue
    for (int i = 0 ; i < height  ; i++)
    {
        for (int j = 0 ; j < width  ; j++)
        {
            r = image[i][j].rgbtRed ;
            g = image[i][j].rgbtGreen ;
            b = image[i][j].rgbtBlue ;
            // average = red + green + blue / 3
            av = (r + g + b) / 3 ;
            average =  round(av);
            //return the average to image.red.green.blue to make them equal to give gray colour
            image[i][j].rgbtRed = average ;
            image[i][j].rgbtBlue = average ;
            image[i][j].rgbtGreen = average ;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float r ;
    float g ;
    float b ;
    float sred ;
    float sblue ;
    float sgreen ;
    int sepiared ;
    int sepiagreen ;
    int sepiablue ;
    // loop around the image

    for (int i = 0 ; i < height  ; i++)
    {
        for (int j = 0 ; j < width  ; j++)
        {
            //apply the sepia forumuala to give the rediush brown effect
            r = image[i][j].rgbtRed ;
            g = image[i][j].rgbtGreen ;
            b = image[i][j].rgbtBlue ;
            sred = (r * 0.393) + (g * 0.769) + (b * 0.189);
            // to not go over the limmit of 8 bit == 255 
            if (sred > 255)
            {
                sred = 255 ;
            }
            sgreen = (r * 0.349) + (g * 0.686) + (b * 0.168);
            if (sgreen > 255)
            {
                sgreen = 255 ;
            }
            sblue = (r * 0.272) + (g * 0.534) + (b * 0.131) ;
            if (sblue > 255)
            {
                sblue = 255 ;
            }
            //round the number
            sepiared =  round(sred) ;
            sepiagreen =  round(sgreen) ;
            sepiablue =  round(sblue) ;
            image[i][j].rgbtRed = sepiared ;
            image[i][j].rgbtGreen = sepiagreen ;
            image[i][j].rgbtBlue = sepiablue ;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through image rows
    for (int i = 0; i < height; i++)
    {
        //loop through image pixels
        for (int j = 0; j < width / 2; j++)
        {
            // put the value of red green blue in int as extra buffer
            //swap image as 2 equal half and move the right half to left have in buffer then swap it and return left half to right again
            int swapBlue = image[i][j].rgbtBlue;
            int swapGreen = image[i][j].rgbtGreen;
            int swapRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtBlue = swapBlue;
            image[i][width - j - 1].rgbtGreen = swapGreen;
            image[i][width - j - 1].rgbtRed = swapRed;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    float counter;
    RGBTRIPLE temp[height][width];
    //loop through the image
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            counter = 0.00;
            // 2d deminanioal array  3x3 

            for (int k = -1; k < 2; k++)
            {
                // make sure the edge byte get 6 byte 2x3 array  and if they are in matrix get 2x2 array only
                //continue make the loop go to the next loop and ingoroe this case here
                
                if (j + k < 0 || j + k > height - 1)
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)
                    {
                        continue;
                    }
                    // put the 9 byte in 3 x3 array the calcalate the average red green and blue

                    sumBlue += image[j + k][i + h].rgbtBlue;
                    sumGreen += image[j + k][i + h].rgbtGreen;
                    sumRed += image[j + k][i + h].rgbtRed;
                    counter++;
                }
            }

            // averages the sum to make picture look blurrier
            temp[j][i].rgbtBlue = round(sumBlue / counter);
            temp[j][i].rgbtGreen = round(sumGreen / counter);
            temp[j][i].rgbtRed = round(sumRed / counter);
        }
    }

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }
}