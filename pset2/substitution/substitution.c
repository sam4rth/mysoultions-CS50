#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void error(int argi, string key);
string encipher(string plaintext, string key);
//Taking KEY as input DONE
int main(int argc, string argv[])
{
    //start the string with 1, args[0]= "substitution.c" (file name)

    //first error check, here because we need to check is there was a key or not befor we send it to key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        exit(1);
    }

    string key = argv[1];
    error(argc, key);
    int i, j = strlen(key);
    for (i = 0; i <= j; i++)
    {
        key[i] = toupper(key[i]);
    }

    string plain = get_string("Plaintext : ");

    printf("ciphertext: ");
    puts(encipher(plain, key));
    //printf("\n");
}

//Encipher
string encipher(string plaintext, string key)
{
    //char a[] = {'a','b','c','d','e','f','g','h','i','','','','','','','','','','','','','','','','',''}
    int text[27];
    int l = strlen(plaintext);
    int i = 0, j = 0, k = 0, m = 0;
    for (i = 65; i <= 90; i++)
    {
        text[j] = i - (int)key[j];
        //printf("%d",text[j]);
        j++;
    }
    j = 0;
    m = 0;
    //Take the letter first to last //k is the index number for plaintext -> plaintext[k] //l is the length of the plaintext
    for (k = 0; k < l; k++)
    {
        m = 0;
        //go through all the alphapbets A - Z and a - z and find the letter it is.
        for (i = 65; i <= 90; i++, m++)
        {
            // A - Z
            if ((int)plaintext[k] == i)
            {
                //printf("%c ->", plaintext[k]);
                plaintext[k] = (int)plaintext[k] - text[m];
                //printf(" %c\n", plaintext[k]);
                break;

            }

        }
        m = 0;
        //go through all the alphapbets A - Z and a - z and find the letter it is.
        for (i = 97; i <= 122; i++, m++)
        {
            // a - z
            if ((int)plaintext[k] == i)
            {
                //printf("%c ->", plaintext[k]);
                plaintext[k] = (int)plaintext[k] - text[m];
                //printf(" %c\n", plaintext[k]);
                break;

            }

        }

    }


    //  puts(plaintext);
    return plaintext;
}

//Validating Done
void error(int argi, string key)
{
    //this funtion checks for any error int the entry of the 26 Alphabets

    int s = strlen(key), j = 0, i = 0;
    //start...

    //if the key has 26 letters
    if (s != 26)
    {
        printf("Usage: Key must contain 26 characters its %d chareacters.\n", s);
        exit(1);
    }

    //if the key has only alphabet
    for (i = 0; i < s; i++)
    {
        if ((int)key[i] < 65 || ((int)key[i] > 90 && (int)key[i] < 97) || (int)key[i] > 122)
        {
            printf("Usage: KEY shoud only have alphabets %c\n", key[i]);
            exit(1);
        }
    }

    //if the key has some letter repeated
    for (i = 0; i < s; i++)
    {
        for (j = 1 + i; j < s; j++)
        {
            if (key[i] == key[j])
            {
                printf("Usage: KEY shoud not contain any repeated letter - %c", key[i]);
                exit(1);
            }
        }
    }


}

// Dec  Char                           Dec  Char     Dec  Char     Dec  Char
// ---------                           ---------     ---------     ----------
//   0  NUL (null)                      32  SPACE     64  @         96  `
//   1  SOH (start of heading)          33  !         65  A         97  a
//   2  STX (start of text)             34  "         66  B         98  b
//   3  ETX (end of text)               35  #         67  C         99  c
//   4  EOT (end of transmission)       36  $         68  D        100  d
//   5  ENQ (enquiry)                   37  %         69  E        101  e
//   6  ACK (acknowledge)               38  &         70  F        102  f
//   7  BEL (bell)                      39  '         71  G        103  g
//   8  BS  (backspace)                 40  (         72  H        104  h
//   9  TAB (horizontal tab)            41  )         73  I        105  i
//  10  LF  (NL line feed, new line)    42  *         74  J        106  j
//  11  VT  (vertical tab)              43  +         75  K        107  k
//  12  FF  (NP form feed, new page)    44  ,         76  L        108  l
//  13  CR  (carriage return)           45  -         77  M        109  m
//  14  SO  (shift out)                 46  .         78  N        110  n
//  15  SI  (shift in)                  47  /         79  O        111  o
//  16  DLE (data link escape)          48  0         80  P        112  p
//  17  DC1 (device control 1)          49  1         81  Q        113  q
//  18  DC2 (device control 2)          50  2         82  R        114  r
//  19  DC3 (device control 3)          51  3         83  S        115  s
//  20  DC4 (device control 4)          52  4         84  T        116  t
//  21  NAK (negative acknowledge)      53  5         85  U        117  u
//  22  SYN (synchronous idle)          54  6         86  V        118  v
//  23  ETB (end of trans. block)       55  7         87  W        119  w
//  24  CAN (cancel)                    56  8         88  X        120  x
//  25  EM  (end of medium)             57  9         89  Y        121  y
//  26  SUB (substitute)                58  :         90  Z        122  z
//  27  ESC (escape)                    59  ;         91  [        123  {
//  28  FS  (file separator)            60  <         92  \        124  |
//  29  GS  (group separator)           61  =         93  ]        125  }
//  30  RS  (record separator)          62  >         94  ^        126  ~
//  31  US  (unit separator)            63  ?         95  _        127  DEL