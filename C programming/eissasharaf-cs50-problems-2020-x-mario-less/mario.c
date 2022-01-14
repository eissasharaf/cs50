#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //define an integer
    int height;
    //prompt the user for a valid height
    do
    {
        height = get_int("height: ");    
    }
    while (height < 1 || height > 8);
    //print out the correct number of lines
    for (int i = 0; i < height; i++)
    {
        //print out the spaces
        for (int m = 0; m < height - i - 1 ; m++) 
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }   
        printf("\n");      
    }
}
