#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    long int card = -1, lsum = 0, icard, i, swi = 1, ci, cswi, ccard;

    while (card < 100)
    {

        card = get_long("Number : ");

    }
    i = 1;
    while (i <= card / 10)
    {
        i *= 10;
        swi++;
    }
    ccard = card;
    ci = i;
    cswi = swi;
    while (swi > 0) //this gives the sum of the digits as stated in the question
    {
        if (swi % 2 == 0)//CHECKS IF IT IS THE 0THER NUMBER
        {
            icard = card / i;
            icard = icard * 2;

            if (icard >= 10)
            {
                lsum = lsum + (icard / 10) + (icard % 10);
            }
            else //CHECKS IF IT IS THE FIRST ONE
            {
                lsum = lsum + icard;
            }
        }
        else
        {
            icard = card / i;
            lsum = lsum + icard;
        }
        swi--;
        card = card % i;
        i = i / 10;

    }

    //AMEX\n or MASTERCARD\n or VISA\n or INVALID\n

    if (lsum % 10 == 0)
    {
        if ((cswi == 13 || cswi == 14 || cswi == 15 || cswi == 16) && (ccard / ci) == 4)
        {
            printf("VISA\n");
            //VISA
        }
        else if (cswi == 16 && (ccard / (ci / 10) == 55 || ccard / (ci / 10) == 54 || ccard / (ci / 10) == 53 || ccard / (ci / 10) == 52
                                || ccard / (ci / 10) == 51))
        {
            printf("MASTERCARD\n");
            //MASTERCARD
        }
        else if (cswi == 15 && (ccard / (ci / 10) == 34 || ccard / (ci / 10) == 37))
        {
            printf("AMEX\n");
            //AMEX
        }
        else
        {
            printf("INVALID\n");
            //INVALID
        }
    }

    else
    {
        printf("INVALID\n");
        // INVALID
    }

//THIS IS THE PROGRAM TO FIND THE
}