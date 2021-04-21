#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
typedef uint8_t BYTE;

typedef struct
{

    BYTE a;
    BYTE b;
    BYTE c;
    BYTE d;

}
chunk;


int main(int argc, char *argv[])
{


    if (argc != 2)
    {
        printf("Usage: ./recover image");
        exit(1);
    }

    chunk r;
    int n = 0;
    char filename[100];
    FILE *card = fopen(argv[1], "r");
    FILE *w = NULL;
    bool first = true, found = false;



    while (fread(&r, sizeof(r), 1, card) > 0)
    {
        if (r.a == 0xff && r.b == 0xd8 && r.c == 0xff && (r.d & 0xf0) == 0xe0)
        {
            found = true;
            if (first)
            {
                first = false;
                w = fopen("000.jpg", "w");
                fwrite(&r, sizeof(r), 1, w);
            }
            else
            {
                fclose(w);
                sprintf(filename, "%03i.jpg", ++n);
                w = fopen(filename, "w");
                fwrite(&r, sizeof(r), 1, w);
            }
        }
        else
        {
            if (found)
            {
                fwrite(&r, sizeof(r), 1, w);
            }
        }
    }
}

// Specification
// Implement a program called recover that recovers JPEGs from a forensic image.

// Implement your program in a file called recover.c in a directory called recover.
// Your program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs.
// If your program is not executed with exactly one command-line argument, it should remind the user of correct usage, and main should return 1.
// If the forensic image cannot be opened for reading, your program should inform the user as much, and main should return 1.
// Your program, if it uses malloc, must not leak any memory.