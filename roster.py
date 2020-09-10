from cs50 import SQL
import sys
import csv

db = SQL("sqlite:///students.db")
list = db.execute("SELECT * FROM students WHERE house LIKE ? ORDER BY last,first", sys.argv[1])
for row in list:
    if row["middle"] == "NULL":
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["last"] + " " + row["last"] + ", born " + str(row["birth"]))