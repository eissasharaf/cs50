from cs50 import get_float

owed = -1

while owed < 0:
    owed = get_float("Change owed: ")
coin = [25, 10, 5, 1]
total = 0
owed = round(owed * 100)
for i in coin:
    total += int(owed / i)
    owed %= i 
print(total)