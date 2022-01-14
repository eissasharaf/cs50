//include libraries
#include<stdio.h>
#include<cs50.h>
#include<math.h>

//main function begin
int main(void)
{
    //variable declearation
    int coin = 0, cent; 
    float dollar;
    
    //prompt the user for a non negative change owed
    do
    {
        dollar = get_float("change owed:");
    }
    while (dollar < 0);

//calculating the number of coins
    cent = round(dollar * 100);
    //quarters
    while (cent >= 25)
    {
        cent -= 25; 
        coin++;
    }
    //dimes
    while (cent >= 10)
    {
        cent -= 10; 
        coin++;
    }
    // nickels
    while (cent >= 5)
    {
        cent -= 5; 
        coin++;
    }
    //pennies  
    while (cent >= 1)
    { 
        cent -= 1; 
        coin++;
    }

    //output  
    printf("%i\n", coin);
}  
//end of main
