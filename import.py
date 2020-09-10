from cs50 import SQL
import sys
import csv


# Creates database
open("students.db", "w").close()
db = SQL("sqlite:///students.db")
# Creates DictReader
reader = csv.DictReader(open(sys.argv[1]))
# Creates table
db.execute("CREATE TABLE students (first TEXT,middle TEXT, last TEXT, house TEXT, birth NUMERIC)")
# Iterates over CSV file
for row in reader:
    # Separates names
    name = row["name"].split()
    # Handles long name
    if (len(name) > 2):
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
        name[0], name[1], name[2], row["house"], row["birth"])
    # Handles short name
    else:
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
        name[0], None, name[1], row["house"], row["birth"])