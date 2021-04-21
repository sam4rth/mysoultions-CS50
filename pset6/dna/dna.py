from sys import argv, exit
import csv

if len(argv) != 3:
    print("Usage: dna.py datab.csv sequence.txt")
    exit(1)

datab = open(argv[1], "r")
datas = open(argv[2], "r")

data = csv.reader(datab)
seq = csv.reader(datas)

strnames = []
strd = {}
sequence = []
userstr = []

i = 0
for row in data:
    if i == 0:
        strnames = row.copy()
    else:
        strd[row[0]] = row.copy()
        strd[row[0]].pop(0)
    i = 1

for row in seq:
    sequence = row.copy()
    seq = sequence[0]
    sequence.clear()

for j in range(1, len(strnames)):
    reps = strnames[j]
    maxreps = 0
    while seq.count(reps) > 0:
        maxreps += 1
        reps += strnames[j]
    userstr.append(str(maxreps))

for items in strd:
    if strd[items] == userstr:
        print(items)
        exit(0)

print("No match")

# Tests
# Run your program as python dna.py databases/small.csv sequences/1.txt. Your program should output Bob.
# Run your program as python dna.py databases/small.csv sequences/2.txt. Your program should output No match.
# Run your program as python dna.py databases/small.csv sequences/3.txt. Your program should output No match.
# Run your program as python dna.py databases/small.csv sequences/4.txt. Your program should output Alice.
# Run your program as python dna.py databases/large.csv sequences/5.txt. Your program should output Lavender.
# Run your program as python dna.py databases/large.csv sequences/6.txt. Your program should output Luna.
# Run your program as python dna.py databases/large.csv sequences/7.txt. Your program should output Ron.
# Run your program as python dna.py databases/large.csv sequences/8.txt. Your program should output Ginny.
# Run your program as python dna.py databases/large.csv sequences/9.txt. Your program should output Draco.
# Run your program as python dna.py databases/large.csv sequences/10.txt. Your program should output Albus.
# Run your program as python dna.py databases/large.csv sequences/11.txt. Your program should output Hermione.
# Run your program as python dna.py databases/large.csv sequences/12.txt. Your program should output Lily.
# Run your program as python dna.py databases/large.csv sequences/13.txt. Your program should output No match.
# Run your program as python dna.py databases/large.csv sequences/14.txt. Your program should output Severus.
# Run your program as python dna.py databases/large.csv sequences/15.txt. Your program should output Sirius.
# Run your program as python dna.py databases/large.csv sequences/16.txt. Your program should output No match.
# Run your program as python dna.py databases/large.csv sequences/17.txt. Your program should output Harry.
# Run your program as python dna.py databases/large.csv sequences/18.txt. Your program should output No match.
# Run your program as python dna.py databases/large.csv sequences/19.txt. Your program should output Fred.
# Run your program as python dna.py databases/large.csv sequences/20.txt. Your program should output No match.