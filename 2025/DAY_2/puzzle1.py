import time

start = time.time()

with open("input.txt", "rt") as file:
    ranges = file.read().split(",")
sum = 0
for r in ranges:
    low, high = r.split("-")
    for num in range(int(low), (int(high) + 1)):
        num = str(num)
        if len(num) % 2 != 0:
            continue
        mid = int(len(num) / 2)
        if num[0:mid] == num[mid:]:
            sum += int(num)
print(sum)
end = time.time()
print(f"{round(end - start, 4)}s")
