#include<stdio.h>
#include<cs50.h>
long number;
void cough(string type);
    
int main(void)
{
    number = get_long("Number:");
    int i = 1;
    long test = number;
    long testt = number;
    while (test > 9)
    {
        test = test / 10; 
        i++;
    }
    if (i == 16)
    {  
        while (testt > 99)
        {
            testt = testt / 10;
        }
        if (testt == 51 || testt == 52 || testt == 53 || testt == 54 || testt == 55)
        {
            cough("MASTERCARD");
        }
        else if (testt / 10 == 4)
        {
            cough("VISA");
        }
        else
        {
            printf("INVALID\n");
        }
        
    }
    else if (i == 15)
    {   
        while (testt > 99)
        {
            testt = testt / 10;
        }
        if (testt == 34 || testt == 37)
        {
            cough("AMEX"); 
        }
        else 
        {
            printf("INVALID\n");
        }
    }
    else if (i == 13)
    {   
        while (testt > 9)
        {
            testt = testt / 10;
        }
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
    if (sum % 10 == 0)
    {
        printf("%s\n", type);
    }
    else 
    {
        printf("INVALID\n");
    }
}


