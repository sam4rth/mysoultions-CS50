#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int i, j, hight = -1;
//This piece of code askes for input till it gets the right one!
    while (hight > 8 || hight < 1)
    {
        hight = get_int("Hight : ");
    }
//this is the main loop
    for (i = 1; i <= hight; i++)
    {
        //this loop is prints the space
        for (j = 0; j < hight - i; j++)
        {
            printf(" ");
        }
        //this prints the #
        for (j = 0 ; j < i ; j++)
        {
            printf("#");
        }
        printf("  ");
        for (j = 0; j < i; j++)
        {
            printf("#");
        }
        //this takes the printing to next line
        printf("\n");

    }
}