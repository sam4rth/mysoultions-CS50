#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
    float cash = -1, owed;
    int coin = 0;

    while (cash <= 0.00)
    {
        cash = get_float("Change owed : ");
    }
    cash = round(cash * 100);

    owed = cash;

    while (cash != 0)
    {
        if (cash >= 25)  // is cash is more than 25 0r 25 cents do this
        {
            cash = cash - 25;
        }
        else if (cash >= 10)  // is cash is more than 10 or 10 cents do this
        {
            cash = cash - 10;
        }
        else if (cash >= 5) // is cash is more than 5 or 5 cents do this
        {
            cash = cash - 5;
        }
        else  // is cash is more than 1 or 1 cents do this
        {
            cash = cash - 1;
        }
        coin++;
        // this addes 1 coin everytime the loop is completed
    }
// this prints the number of coin!
    printf("%d\n", coin);
}