import sys
import csv


def main():

    #making sure there are enough arguments
    if len(sys.argv) < 3:
        print("Usage: python dna.py data.csv sequence.txt")

        sys.exit(1)

    #taking the csv and the dna text files
    csv_file = sys.argv[1]
    dna_file = sys.argv[2]


    all_sequences = []
    dna_sequences = []
    ppl_sequences = []

    with open(csv_file) as f:
        sequences = csv.reader(f)

        #taking each row in sequences and store it in the list called all_sequences
        for row in sequences:
            all_sequences.append(row)

        #taking the STRs from the first row as a dictionary to the dna_sequences list
        for sequence in all_sequences[0]:
            if sequence != "name":
                dna_sequences.append({"str": sequence, "repitition": 0})

        #storing the persons in the ppl_sequences list containing their name as first element and the number of repeats for every STR as the rest elements
        for i in range(1, len(all_sequences)):
            ppl_sequences.append(all_sequences[i])


    #reading the text file
    with open(dna_file) as d:
        dnas = d.read()

        #looping through STRs in the dna_sequences list
        for dna in dna_sequences:
            STR = dna["str"]

            i = 0

            #a variable recording repeat count for each sequence of repeats
            repeat_count = 0

            #a list storing repeat counts for each STR to get the max value later
            repeats = []

            #repeating until the end of the DNAs text
            while(i <= len(dnas)):

                j = i

                #repeat while the STR matches with a DNA from the text
                while dnas[j : j + len(STR)] == STR:

                    #if it matches increment the count and jump to the next DNA from the same size
                    repeat_count += 1

                    j += len(STR)

                #if it doesn't match store the record of the repetition sequence in the repeats list
                repeats.append(repeat_count)

                #resetting the repeat count variable for the next sequence
                repeat_count = 0

                #incrementing i
                i += 1

            #getting the max number of repititions
            max = 0

            for rep in repeats:
                if rep > max:
                    max = rep

            repeats = []

            dna["repitition"] = max


        #getting and storing the max numbers of repititions for each STR by order, the first MAX is for the first STR in the csv file
        repeats_list = []

        for dna in dna_sequences:
            repeats_list.append(dna["repitition"])


        #looping through each person to see if the repeats list matches with him
        for person in ppl_sequences:

            isHim = True

            #comparing every pair of repeats counts, starting with 1 because person[0] is the name of the person
            for j in range(1, len(person)):

                if int(person[j]) != repeats_list[j - 1]:

                    isHim = False

            if isHim:

                print(person[0])

                sys.exit(0)



        print("No match")

        sys.exit(1)


if __name__ == "__main__":
    main()



