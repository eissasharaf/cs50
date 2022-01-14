from sys import argv, exit
from cs50 import SQL
import csv

if(len(argv) != 2):
    print('Usage: python import.py Filename.csv')
    exit(1)

open("students.db", "w").close()
db = SQL("sqlite:///students.db")
db.execute("CREATE TABLE students (id INTEGER,first varchar(255),middle varchar(255),last varchar(255), house varchar(10),birth INTEGER,PRIMARY KEY (id));")
with open(argv[1], 'r') as infile:
    reader = list(csv.DictReader(infile))
    for row in reader:
        name = row['name'].split()
        db.execute("INSERT INTO students (first, middle, last, house, birth) values (?, ?, ?, ?, ?)",
                   name[0], name[1] if len(name) == 3 else None, name[len(name) - 1], row["house"], row["birth"])

