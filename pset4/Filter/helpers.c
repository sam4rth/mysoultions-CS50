#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int h, w, avg;
    float a;

    for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {

            a = (float)(image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.00;

            avg = round(a);

            image[h][w].rgbtRed = avg;

            image[h][w].rgbtGreen = avg;

            image[h][w].rgbtBlue = avg;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int h, w, i, j;
    float sepiaRed, sepiaGreen, sepiaBlue;

    int red[height][width];
    int green[height][width];
    int blue[height][width];

    for (h = 0; h < height; h++)
    {
        for (w = 0; w < width; w++)
        {

            red[h][w] = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            green[h][w] = round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            blue[h][w] = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);


            if (red[h][w] > 255)
            {
                red[h][w] = 255;
            }
            if (green[h][w] > 255)
            {
                green[h][w] = 255;
            }
            if (blue[h][w] > 255)
            {
                blue[h][w] = 255;
            }

        }
    }

    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            image[j][i].rgbtRed = red[j][i];
            image[j][i].rgbtGreen = green[j][i];
            image[j][i].rgbtBlue = blue[j][i];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int h, a, b;
    RGBTRIPLE temp;

    for (h = 0; h < height; h++)
    {
        for (a = 0; a < (width / 2); a++)
        {
            b = (width - 1) - a;
            temp = image[h][a];
            image[h][a] = image[h][b];
            image[h][b] = temp;

        }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // i width, j height, k width of the 3 x 3 gird, m Height of the 3 x 3 gird, avg avg rounded to int;
    int i, j, k, m, avg, rsum = 0, bsum = 0, gsum = 0;

    // a avg in float
    float a;

    int red[height][width];
    int green[height][width];
    int blue[height][width];


    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            if ((i >= 1 && i <= (width - 2)) && (j >= 1 && j <= (height - 2))) // with the center one
            {
                for (k = i - 1; k <= i + 1; k++)
                {
                    for (m = j - 1; m <= j + 1; m++)
                    {
                        rsum = rsum + image[m][k].rgbtRed;
                        gsum = gsum + image[m][k].rgbtGreen;
                        bsum = bsum + image[m][k].rgbtBlue;
                    }
                }

                a = rsum / 9.00;
                red[j][i] = round(a);

                a = gsum / 9.00;
                green[j][i] = round(a);

                a = bsum / 9.00;
                blue[j][i] = round(a);

                a = 0;
                rsum = 0;
                gsum = 0;
                bsum = 0;
            }
            else if ((i == 0 || i == (width - 1)) && (j == 0 || j == (height - 1))) // Corners
            {
                if (i == 0 && j == 0) // upper left
                {
                    for (k = i; k <= i + 1; k++)
                    {
                        for (m = j; m <= j + 1; m++)
                        {
                            rsum = rsum + image[m][k].rgbtRed;
                            gsum = gsum + image[m][k].rgbtGreen;
                            bsum = bsum + image[m][k].rgbtBlue;
                        }
                    }

                    a = rsum / 4.00;
                    red[j][i] = round(a);

                    a = gsum / 4.00;
                    green[j][i] = round(a);

                    a = bsum / 4.00;
                    blue[j][i] = round(a);

                    a = 0;
                    rsum = 0;
                    gsum = 0;
                    bsum = 0;
                }
                else if (i == 0 && j == height - 1) // lower left
                {
                    for (k = i; k <= i + 1; k++)
                    {
                        for (m = height - 2; m <= height - 1; m++)
                        {
                            rsum = rsum + image[m][k].rgbtRed;
                            gsum = gsum + image[m][k].rgbtGreen;
                            bsum = bsum + image[m][k].rgbtBlue;
                        }
                    }

                    a = rsum / 4.00;
                    red[j][i] = round(a);

                    a = gsum / 4.00;
                    green[j][i] = round(a);

                    a = bsum / 4.00;
                    blue[j][i] = round(a);

                    a = 0;
                    rsum = 0;
                    gsum = 0;
                    bsum = 0;
                }
                else if (i == width - 1 && j == height - 1) // upper right
                {
                    for (k = i - 1; k <= width - 1; k++)
                    {
                        for (m = j - 1; m <= height - 1; m++)
                        {
                            rsum = rsum + image[m][k].rgbtRed;
                            gsum = gsum + image[m][k].rgbtGreen;
                            bsum = bsum + image[m][k].rgbtBlue;
                        }
                    }

                    a = rsum / 4.00;
                    red[j][i] = round(a);

                    a = gsum / 4.00;
                    green[j][i] = round(a);

                    a = bsum / 4.00;
                    blue[j][i] = round(a);

                    a = 0;
                    rsum = 0;
                    gsum = 0;
                    bsum = 0;
                }
                else if (i == width - 1 && j == 0) // lower right
                {
                    for (k = i - 1; k <= width - 1; k++)
                    {
                        for (m = j; m <= j + 1; m++)
                        {
                            rsum = rsum + image[m][k].rgbtRed;
                            gsum = gsum + image[m][k].rgbtGreen;
                            bsum = bsum + image[m][k].rgbtBlue;
                        }
                    }

                    a = rsum / 4.00;
                    red[j][i] = round(a);

                    a = gsum / 4.00;
                    green[j][i] = round(a);

                    a = bsum / 4.00;
                    blue[j][i] = round(a);

                    a = 0;
                    rsum = 0;
                    gsum = 0;
                    bsum = 0;
                }
            }
            else if ((i == 0) || (j == 0) || (i == width - 1) || (j == height - 1)) // Edges
            {
                if (i == 0) // Left
                {
                    for (k = i; k <= i + 1; k++)
                    {
                        for (m = j - 1; m <= j + 1; m++)
                        {
                            rsum = rsum + image[m][k].rgbtRed;
                            gsum = gsum + image[m][k].rgbtGreen;
                            bsum = bsum + image[m][k].rgbtBlue;
                        }
                    }

                    a = rsum / 6.00;
                    red[j][i] = round(a);

                    a = gsum / 6.00;
                    green[j][i] = round(a);

                    a = bsum / 6.00;
                    blue[j][i] = round(a);

                    a = 0;
                    rsum = 0;
                    gsum = 0;
                    bsum = 0;
                }
                else if (j == 0) // Top
                {
                    for (k = i - 1; k <= i + 1; k++)
                    {
                        for (m = j; m <= j + 1; m++)
                        {
                            rsum = rsum + image[m][k].rgbtRed;
                            gsum = gsum + image[m][k].rgbtGreen;
                            bsum = bsum + image[m][k].rgbtBlue;
                        }
                    }

                    a = rsum / 6.00;
                    red[j][i] = round(a);

                    a = gsum / 6.00;
                    green[j][i] = round(a);

                    a = bsum / 6.00;
                    blue[j][i] = round(a);

                    a = 0;
                    rsum = 0;
                    gsum = 0;
                    bsum = 0;
                }
                else if (i == width - 1) // Right
                {
                    for (k = i - 1; k <= i; k++)
                    {
                        for (m = j - 1; m <= j + 1; m++)
                        {
                            rsum = rsum + image[m][k].rgbtRed;
                            gsum = gsum + image[m][k].rgbtGreen;
                            bsum = bsum + image[m][k].rgbtBlue;
                        }
                    }

                    a = rsum / 6.00;
                    red[j][i] = round(a);

                    a = gsum / 6.00;
                    green[j][i] = round(a);

                    a = bsum / 6.00;
                    blue[j][i] = round(a);

                    a = 0;
                    rsum = 0;
                    gsum = 0;
                    bsum = 0;
                }
                else if (j == height - 1) // Bottom
                {
                    for (k = i - 1; k <= i + 1; k++)
                    {
                        for (m = j - 1; m <= j; m++)
                        {
                            rsum = rsum + image[m][k].rgbtRed;
                            gsum = gsum + image[m][k].rgbtGreen;
                            bsum = bsum + image[m][k].rgbtBlue;
                        }
                    }

                    a = rsum / 6.00;
                    red[j][i] = round(a);

                    a = gsum / 6.00;
                    green[j][i] = round(a);

                    a = bsum / 6.00;
                    blue[j][i] = round(a);

                    a = 0;
                    rsum = 0;
                    gsum = 0;
                    bsum = 0;
                }
            }
        }
    }


    // setting the values

    for (i = 0; i < width; i++)
    {
        for (j = 0; j < height; j++)
        {
            image[j][i].rgbtRed = red[j][i];
            image[j][i].rgbtGreen = green[j][i];
            image[j][i].rgbtBlue = blue[j][i];
        }
    }
    return;
}
//   sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
//   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
//   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

// Specification
// Implement the functions in helpers.c such that a user can apply grayscale, sepia, reflection, or blur filters to their images.

// The function grayscale should take an image and turn it into a black-and-white version of the same image.
// The function sepia should take an image and turn it into a sepia version of the same image.
// The reflect function should take an image and reflect it horizontally.
// Finally, the blur function should take an image and turn it into a box-blurred version of the same image.
// You should not modify any of the function signatures, nor should you modify any other files other than helpers.c.

//   sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
//   sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
//   sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

// Specification
// Implement the functions in helpers.c such that a user can apply grayscale, sepia, reflection, or blur filters to their images.

// The function grayscale should take an image and turn it into a black-and-white version of the same image.
// The function sepia should take an image and turn it into a sepia version of the same image.
// The reflect function should take an image and reflect it horizontally.
// Finally, the blur function should take an image and turn it into a box-blurred version of the same image.
// You should not modify any of the function signatures, nor should you modify any other files other than helpers.c.

