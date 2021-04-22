from cs50 import SQL
import sys
import csv

# Wrong Usage Check
if (len(sys.argv) != 2):
    print("Usage: python import.py nameofthefile.csv")
    exit()

db = SQL("sqlite:///students.db")

name = "name"
spname = name.split()

firt_name = "Samarth"
middle_name = "Alok"
last_name = "Srivastava"

# print(f"Hello {sys.argv[1]}")
count = 0

# CSV --> name,house,birth
# DataBASE ==> first,middle,last,house,birth
# openning and storing the csv file in memory.
with open(sys.argv[1], "r") as data:

    l = csv.reader(data)

    count = len(sys.argv[1].split())
    next(l)

    for line in l:
        name = line[0]
        spname = name.split()
        count = len(spname)
        if count == 2:
            first_name = spname[0]
            middle_name = "None"
            last_name = spname[1]
            db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?)",
                       first_name, None, last_name, line[1], line[2])
        elif count == 3:
            first_name = spname[0]
            middle_name = spname[1]
            last_name = spname[2]
            db.execute("INSERT INTO students (first,middle,last,house,birth) VALUES (?,?,?,?,?)",
                       first_name, middle_name, last_name, line[1], line[2])