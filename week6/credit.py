import math
from cs50 import get_int

ccNumber = get_int("Number: ")

number = str(ccNumber)

length = len(number)

first_sum = 0
second_sum = 0;

if length % 2 == 0:

    for i in range(0, length, 2):
        double = int(number[i]) * 2

        if double > 9:
            double = math.floor(double / 10) + double % 10

        first_sum += double

    for j in range(1, length, 2):
        second_sum += int(number[j])

else:

    for i in range(1, length, 2):
        double = int(number[i]) * 2

        if double > 9:
            double = math.floor(double / 10) + double % 10

        first_sum += double

    for j in range(0, length, 2):
        second_sum += int(number[j])

sum = first_sum + second_sum

if sum % 10 != 0:
    print("INVALID")

elif length >= 13 and length <= 16:

    if number[0] == "4":
        print("VISA")

    elif length == 15:
        if number[0: 2] in ["34", "37"]:
            print("AMEX")

    elif length == 16:
        if number[0: 2] in ["51", "52", "53", "54", "55"]:
            print("MASTERCARD")


    else:
        print("INVALID")

else:
    print("INVALID")

