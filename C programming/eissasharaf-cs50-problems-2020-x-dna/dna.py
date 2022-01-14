from sys import argv, exit
import csv


def main():
    if not len(argv) == 3:
        print('Usage: python dna.py data.csv sequence.txt')
        exit(1)
    STR = open(argv[2], 'r')
    person = STR.read()
    data = load(argv[1])
    repeat = count(data, person)
    name = compare(data, repeat)
    if name != None:
        print(name)
    else:
        print('No match')


def load(database):
    data = dict()
    with open(database, 'r') as infile:
        reader = csv.reader(infile)
        count = 0
        for row in reader:
            if count == 0:
                for word in row:
                    data[word] = list()
                count += 1
                key = list(data.keys())
            else:
                for i in range(len(row)):
                    data[key[i]].append(row[i])
    return data


def count(data, person):
    key = list(data.keys())
    repeat = list()
    del(key[0])
    for i in range(len(key)):
        repeat.append(0)
        for j in range(len(person)):
            tmp = search(key[i], person[j: len(person)])
            if tmp > repeat[len(repeat) - 1]:
                repeat[len(repeat) - 1] = tmp
    return repeat


def search(dna, person):
    if len(person) < len(dna):
        return 0
    if dna == person[0: len(dna)]:
        repeat = search(dna, person[len(dna): len(person)])
        return repeat + 1
    else:
        return 0


def compare(data, repeat):
    ar = list(data.values())
    qw = list(data.keys())
    for j in range(len(ar[0])):
        if repeat == [int(ar[i + 1][j]) for i in range(len(ar) - 1)]:
            return ar[0][j]


main()
