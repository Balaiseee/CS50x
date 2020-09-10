from cs50 import SQL
import sys
import csv

open("students.db", "w").close()
db = SQL("sqlite:///students.db")
reader = csv.DictReader(open(sys.argv[1]))
db.execute("CREATE TABLE students (first TEXT,middle TEXT, last TEXT, house TEXT, birth NUMERIC)")
for row in reader:
    name = row["name"].split()
    if (len(name) > 2):
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", name[0], name[1], name[2], row["house"], row["birth"])
    else:
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", name[0], None, name[1], row["house"], row["birth"])