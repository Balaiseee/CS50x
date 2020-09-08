import sys
import csv
import re


def letters(input): # Filters a string to  only contain letters
    valids = []
    for character in input:
        if character.isalpha():
            valids.append(character)
    return ''.join(valids)


def parse():
    # Handles STR parse and read in array
    sequence = ""
    with open(sys.argv[2], 'r') as txtfile:
        fluxsequence = csv.reader(txtfile)
        for row in fluxsequence:
            sequence = str(row)
    sequencelist = []
    for element in letters(list(sequence)):
        sequencelist.append(element)
    # Handles database parse and read in dictionnary
    database = csv.DictReader(open(sys.argv[1]))
    return sequencelist, database


def compute():
    (sequence, database) = parse()
    # Converts list into string
    sequence = ''.join(map(str, sequence))
    # Finds number of consecutive TTTTTTCT sequence
    TTTTTTCT = max([len(x) // len("TTTTTTCT") for x in re.findall(r'((?:TTTTTTCT)+)', sequence)], default=0)
    # Finds number of consecutive AGATC sequence
    AGATC = max([len(x) // len("AGATC") for x in re.findall(r'((?:AGATC)+)', sequence)], default=0)
    # Finds number of consecutive TCTAG sequence
    TCTAG = max([len(x) // len("TCTAG") for x in re.findall(r'((?:TCTAG)+)', sequence)], default=0)
    # Finds number of consecutive TATC sequence
    TATC = max([len(x) // len("TATC") for x in re.findall(r'((?:TATC)+)', sequence)], default=0)
    # Finds number of consecutive AATG sequence
    AATG = max([len(x) // len("AATG") for x in re.findall(r'((?:AATG)+)', sequence)], default=0)
    # Finds number of consecutive GATA sequence
    GATA = max([len(x) // len("GATA") for x in re.findall(r'((?:GATA)+)', sequence)], default=0)
    # Finds number of consecutive GAAA sequence
    GAAA = max([len(x) // len("GAAA") for x in re.findall(r'((?:GAAA)+)', sequence)], default=0)
    # Finds number of consecutive TCTG sequence
    TCTG = max([len(x) // len("TCTG") for x in re.findall(r'((?:TCTG)+)', sequence)], default=0)
    for row in database:
        # Handles large database comparison
        if(len(row)==9 and int(row["AGATC"])==AGATC and int(row["TTTTTTCT"])==TTTTTTCT and int(row["AATG"])==AATG and int(row["TCTAG"])==TCTAG and int(row["GATA"])==GATA and int(row["TATC"])==TATC and int(row["GAAA"])==GAAA and int(row["TCTG"])==TCTG):
            return str(row["name"])
        # Handles small database comparison
        if(len(row)==4 and int(row["AATG"])==AATG and int(row["TATC"])==TATC and int(row["AGATC"])==AGATC):
            return str(row["name"])
    return "No match"


print(compute())