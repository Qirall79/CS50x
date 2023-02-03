#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long ccNumber = get_long("Number: ");
    long ccNumber1 = ccNumber;
    long ccNumber2 = ccNumber;

    int sum1 = 0;
    int sum2 = 0;
    int sum = 0;

    long thirteen = 1000000000000;
    long fourteen = 10000000000000;
    long fifteen  = 100000000000000;
    long sixteen  = 1000000000000000;

    string creditCard = "";


    while(ccNumber1 != 0)
    {
        int secondDigit = ((ccNumber1 % 100) - (ccNumber1 % 10)) / 10;

        sum1 += (floor(secondDigit * 2/10) + ((secondDigit * 2) % 10));

        ccNumber1 = floor(ccNumber1 / 100);
    }

     while(ccNumber2 != 0)
    {
        int firstDigit = ccNumber2 % 10;

        sum2 += firstDigit;

        ccNumber2 = floor(ccNumber2 / 100);
    }

    sum = sum1 + sum2;

    if(sum % 10 == 0)
    {

        if(ccNumber >= fifteen && ccNumber < sixteen)
        {
            int first2Digits = floor(ccNumber / fourteen);
            int firstDigit = floor(first2Digits / 10);

            if( first2Digits == 34 || first2Digits == 37)
            {
                creditCard = "AMEX\n";
            }
            else if(firstDigit == 4)
            {
                creditCard = "VISA\n";
            }
            else
            {
                creditCard = "INVALID\n";
            }
        }

        else if(ccNumber >= sixteen && ccNumber < sixteen * 10)
        {
            int first2Digits = floor(ccNumber / (sixteen / 10));
             int firstDigit = floor(first2Digits / 10);

            if(first2Digits >= 51 && first2Digits <= 55)
            {
                creditCard = "MASTERCARD\n";
            }
            else if(firstDigit == 4)
            {
                creditCard = "VISA\n";
            }
            else
            {
                creditCard = "INVALID\n";
            }
        }

        else if(ccNumber >= thirteen && ccNumber < fifteen)
        {
            int first2Digits = 0;

            if(ccNumber >= thirteen && ccNumber < fourteen)
            {
                first2Digits = floor(ccNumber / thirteen);
            }
            if(ccNumber >= fourteen && ccNumber < fifteen)
            {
                first2Digits = floor(ccNumber / fourteen);
            }

            if(first2Digits == 4)
            {
                creditCard = "VISA\n";
            }
            else
            {
                creditCard = "INVALID\n";
            }


        }

        else
        {
            creditCard = "INVALID\n";
        }

    }

    else
    {
        creditCard = "INVALID\n";
    }

    printf("%s", creditCard);



}