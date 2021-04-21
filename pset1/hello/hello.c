#include <stdio.h>
#include <cs50.h>

int main(void)//main function
{
    
    string name = get_string("What is your name?\n");//Asks the user to enter their name, and stores the input in name
    printf("Hello, %s \n", name);// prints the hello message acording to the user input...
    
}