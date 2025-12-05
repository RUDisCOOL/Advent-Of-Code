import time

start = time.time()

with open("input.txt", "rt") as file:
    banks = file.read().splitlines()
sum = 0
for bank in banks:
    bat_l = int(bank[len(bank) - 2])
    bat_r = int(bank[len(bank) - 1])
    for idx in range(len(bank) - 2, -1, -1):
        n = int(bank[idx])
        if n >= bat_l:
            temp = bat_l
            bat_l = n
            if temp > bat_r:
                bat_r = temp

    sum += bat_l * 10 + bat_r
print(sum)
end = time.time()
print(f"{round(end - start, 4)}s")
