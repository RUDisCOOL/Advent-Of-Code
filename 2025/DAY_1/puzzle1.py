with open("input.txt", "rt") as file:
    lines = file.read().splitlines()

cur = 50
count = 0

for line in lines:
    dir = line[:1]
    val = int(line[1:])
    cur = (cur - val if dir == "L" else cur + val) % 100
    if cur == 0:
        count += 1

print(count)
