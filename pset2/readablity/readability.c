#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int lettercount(string text, int length);

int main(void)
{
    string text = get_string("Text : ");
    int length = strlen(text);

    int grade = lettercount(text, length);

    if (grade <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade);
    }

}

int lettercount(string text, int length)
{
    int letters = 0, letters2 = 0, words = 1, sentence = 0;
    float L, S, index;
    //Letter Counter 65 && 90 || 97 && 122
    for (int i = 0; i <= length; i++)
    {
        if (((int)text[i] >= 65 && (int)text[i] <= 90) || ((int)text[i] >= 97 && (int)text[i] <= 122))
        {
            letters++;
            letters2++;
        }
        else if ((int)text[i] == 32)
        {
            words++;
        }
        else if (33 == (int)text[i] || 46 == (int)text[i] || 63 == (int)text[i])
        {
            sentence++;
        }


    }

    L = (letters / (float)words) * 100;// is the average number of letters per 100 words in the text
    S = (sentence / (float)words) * 100;//S is the average number of sentences per 100 words in the text
    index = 0.0588 * L - 0.296 * S - 15.8;
    int grade = round(index);


    // printf("\n%d letter(s)\n",letters);
    // printf("%d word(s)\n",words);
    // printf("%d sentences(s)\n",sentence);
    return grade;
}
//It was a bright cold day in April, and the clocks were striking thirteen. Winston Smith, his chin nuzzled into his breast in an effort to escape the vile wind, slipped quickly through the glass doors of Victory Mansions, though not quickly enough to prevent a swirl of gritty dust from entering along with him.
//33 46 63