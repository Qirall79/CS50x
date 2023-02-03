from cs50 import get_string

text = get_string("Text: ")

alphabets = "abcdefghijklmnopqrstuvwxyz"

l = 0
w = 1
s = 0

length = len(text)

for i in range(length):

    if text[i].lower() in alphabets:

        l += 1

    if text[i] == " ":

        w += 1

    if text[i] in [".", "!", "?"]:

        s += 1

L = l * 100 / w
S = s * 100 / w
grade = round(0.0588 * L - 0.296 * S - 15.8)

if grade > 16:
    print("Grade 16+");

elif grade < 1:
    print("Before Grade 1");

else:
    print(f"Grade {grade}")