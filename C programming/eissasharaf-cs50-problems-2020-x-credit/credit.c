//include librraries
#include<stdio.h>
#include<cs50.h>

//dfinre global variable
long number;

//define functions
void cough(string type);

//main function begin    
int main(void)
{
    //prompt the user for card number
    number = get_long("Number:");

    //define variables
    int i = 1;
    long test = number;
    long testt = number;

    //get the first digit of the number and check the number of digit
    while (test > 9)
    {
        test = test / 10; 
        i++;
    }
    //if the card consists of 16 digit
    if (i == 16)
    {  
        //get the first two digits
        while (testt > 99)
        {
            testt = testt / 10;
        }
        //check for master card
        if (testt == 51 || testt == 52 || testt == 53 || testt == 54 || testt == 55)
        {
            cough("MASTERCARD");
        }
        //check for visa
        else if (testt / 10 == 4)
        {
            cough("VISA");
        }
        else
        {
            printf("INVALID\n");
        }
        
    }
    //if the card consists of 16 digit
    else if (i == 15)
    {   
        //get the first two digits
        while (testt > 99)
        {
            testt = testt / 10;
        }
        //check for american express
        if (testt == 34 || testt == 37)
        {
            cough("AMEX"); 
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    //if the card consists of 13 digit
    else if (i == 13)
    {   
        //get the first two digits
        while (testt > 9)
        {
            testt = testt / 10;
        }
        //check for visa
        if (testt == 4)
        {
            cough("VISA"); 
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }    
}

//algorithms to check if the card is valid
void cough(string type)
{
    int one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, fourteen, fifteen, sixteen;
    one = number % 10;                       
    two = (number / 10) % 10 ;  
    three = (number / 100) % 10 ;
    four = (number / 1000) % 10 ;
    five = (number / 10000) % 10 ;
    six = (number / 100000) % 10 ;
    seven = (number / 1000000) % 10 ;
    eight = (number / 10000000) % 10 ;
    nine = (number / 100000000) % 10 ;
    ten = (number / 1000000000) % 10 ;
    eleven = (number / 10000000000) % 10 ;
    twelve = (number / 100000000000) % 10 ;
    thirteen = (number / 1000000000000) % 10 ;
    fourteen = (number / 10000000000000) % 10 ;
    fifteen = (number / 100000000000000) % 10 ;
    sixteen = (number / 1000000000000000) % 10 ;
    sixteen *= 2;
    fourteen *= 2;
    twelve *= 2;
    ten *= 2;
    eight *= 2;
    six *= 2;
    four *= 2;
    two *= 2; 
    if (two >= 10)
    {
        two = (two % 10) + 1;
    }
    if (four >= 10)
    {
        four = (four % 10) + 1;
    }
    if (six >= 10)
    {
        six = (six % 10) + 1;
    }
    if (eight >= 10)
    {
        eight = (eight % 10) + 1;
    }
    if (ten >= 10)
    {
        ten = (ten % 10) + 1;
    }
    if (twelve >= 10)
    {
        twelve = (twelve % 10) + 1;
    }
    if (fourteen >= 10)
    { 
        fourteen = (fourteen % 10) + 1;
    }
    if (sixteen >= 10)
    {
        sixteen = (sixteen % 10) + 1;
    }
    int sum = one + two + three + four + five + six + seven + eight + nine + ten + eleven + twelve + thirteen + fourteen + fifteen +
              sixteen;
    //card valid          
    if (sum % 10 == 0)
    {
        printf("%s\n", type);
    }
    //card invalid
    else 
    {
        printf("INVALID\n");
    }
}
//end of function 
