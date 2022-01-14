from sys import argv, exit
from cs50 import SQL

if(len(argv) != 2):
    print("Usage: python roster.py Housename")
    exit(1)

db = SQL("sqlite:///students.db")
people = list(db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1]))
for line in people:
  #  print(line['first'], line['middle'] if line['middle'] != None else '', line['last'] + ", born", line['birth'])
    print(f"{line['first']} {line['middle'] + ' ' if line['middle'] != None else ''}{line['last']}, born {line['birth']}")