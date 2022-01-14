#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //define a variable to store the height of the pyrimed
    int height;

    //prompt the user for a valid height
    do
    {
        height = get_int("height: ");    
    }
    while (height < 1 || height > 8);

    //printing the pyramid
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height - 1 - i; j++)
        {
            printf(" ");
        }
        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
