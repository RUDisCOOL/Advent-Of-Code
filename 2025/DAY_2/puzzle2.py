import time
import math

start = time.time()

with open("input.txt", "rt") as file:
    ranges = file.read().split(",")
sum = 0
for r in ranges:
    low, high = r.split("-")
    for num in range(int(low), (int(high) + 1)):
        num = str(num)
        if len(num) < 2:
            continue
        # Code here for flag
        pat_mat = False
        for idx in range(math.floor(len(num) / 2)):
            if pat_mat:
                break
            pat = num[: idx + 1]
            if len(num) % len(pat) != 0:
                continue

            for first_idx in range(idx + 1, len(num), len(pat)):
                secnd_idx = first_idx + len(pat)
                temp = num[first_idx:secnd_idx]
                if temp != pat:
                    break
                if secnd_idx == len(num):
                    # print(f"{num}-{first_idx}-{pat}-{temp}")
                    pat_mat = True
                    break
        if pat_mat:
            sum += int(num)

print(sum)
end = time.time()
print(f"{round(end - start, 4)}s")
