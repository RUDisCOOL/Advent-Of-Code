with open("input.txt", "rt") as file:
    lines = file.read().splitlines()

cur = 50
count = 0

for line in lines:
    dir = line[:1]
    val = int(line[1:])
    div, mod = divmod(val, 100)
    count += div
    if dir == "L":
        if cur != 0 and (cur - mod) <= 0:
            count += 1
        cur = (cur - mod) % 100
    else:
        if (cur + mod) > 99:
            count += 1
        cur = (cur + mod) % 100

print(count)
