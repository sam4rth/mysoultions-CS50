from cs50 import SQL
import sys

# Wrong Usage Check
if (len(sys.argv) != 2):
    print("Usage: python roster.py house")
    exit()

db = SQL("sqlite:///students.db")

# Execute the sqlit command to get a list and store it in memory.
data = db.execute("SELECT first,middle,last,birth FROM students WHERE house = ? ORDER BY last,first;", sys.argv[1])

# Print the names and the date of birth
for rows in data:
    first = rows['first']
    middle = rows['middle']
    last = rows['last']
    birth = rows['birth']

    if middle == None:
        middle = ""
    else:
        middle = middle+" "

    print(f"{first} {middle}{last}, born {birth}")
