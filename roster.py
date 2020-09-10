from cs50 import SQL
import sys
import csv


# Loads databse
db = SQL("sqlite:///students.db")
# Retrieves the list of students of the school entered by the user
list = db.execute("SELECT * FROM students WHERE house LIKE ? ORDER BY last,first ASC", sys.argv[1])
# Handles the display
for row in list:
    if row["middle"] == None:
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))