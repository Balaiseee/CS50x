import sys
import csv
import re


# Filters a string to only contain letters
def letters(input):
    valids = []
    for character in input:
        if character.isalpha():
            valids.append(character)
    return ''.join(valids)


# Handles STR parse and reads in array
def parse():
    sequence = next(csv.reader(open(sys.argv[2])))
    sequencelist = []
    for element in letters(list(sequence)):
        sequencelist.append(element)
    # Handles database parse and reads in dictionnary
    database = csv.DictReader(open(sys.argv[1]))
    return sequencelist, database


def compute():
    (sequence, database) = parse()
    # Converts a list into a string
    sequence = ''.join(sequence)
    # Finds the highest number of TTTTTTCT in a row
    TTTTTTCT = max([len(x) // len("TTTTTTCT") for x in re.findall(r'((?:TTTTTTCT)+)', sequence)], default=0)
    # Finds the highest number of AGATC in a row
    AGATC = max([len(x) // len("AGATC") for x in re.findall(r'((?:AGATC)+)', sequence)], default=0)
    # Finds the highest number of TCTAG in a row
    TCTAG = max([len(x) // len("TCTAG") for x in re.findall(r'((?:TCTAG)+)', sequence)], default=0)
    # Finds the highest number of TATC in a row
    TATC = max([len(x) // len("TATC") for x in re.findall(r'((?:TATC)+)', sequence)], default=0)
    # Finds the highest number of AATG in a row
    AATG = max([len(x) // len("AATG") for x in re.findall(r'((?:AATG)+)', sequence)], default=0)
    # Finds the highest number of GATA in a row
    GATA = max([len(x) // len("GATA") for x in re.findall(r'((?:GATA)+)', sequence)], default=0)
    # Finds the highest number of GAAA in a row
    GAAA = max([len(x) // len("GAAA") for x in re.findall(r'((?:GAAA)+)', sequence)], default=0)
    # Finds the highest number of TCTG in a row
    TCTG = max([len(x) // len("TCTG") for x in re.findall(r'((?:TCTG)+)', sequence)], default=0)
    for row in database:
        # Handles large database comparison
        if(len(row) == 9 and int(row["AGATC"]) == AGATC and int(row["TTTTTTCT"]) == TTTTTTCT and int(row["AATG"]) == AATG and int(row["TCTAG"]) == TCTAG and int(row["GATA"]) == GATA and int(row["TATC"]) == TATC and int(row["GAAA"]) == GAAA and int(row["TCTG"]) == TCTG):
            return row["name"]
        # Handles small database comparison
        if(len(row) == 4 and int(row["AATG"]) == AATG and int(row["TATC"]) == TATC and int(row["AGATC"]) == AGATC):
            return row["name"]
    return "No match"


print(compute())