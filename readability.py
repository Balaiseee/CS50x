from cs50 import get_string
import re
import math
# Gets text from user
text = get_string("Text: ")
# Finds & counts all sentences
sentences = sum([text.count(key) for key in '.?!'])
# Finds & counts all words (here the non-whitespace patterns)
words = len(re.findall(r'(\S+)', text))
# Finds & counts all letters
letters = sum([text.count(key) for key in 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'])
# Calculates the Coleman-Liau index
ColemanLiau_index = round(0.0588 * letters/words*100 - 0.296 * sentences/words*100 - 15.8)
# Manages the display of grades
if (ColemanLiau_index < 1):
    print("Before Grade 1")
elif (ColemanLiau_index > 16):
    print("Grade 16+")
else:
    print("Grade", ColemanLiau_index)