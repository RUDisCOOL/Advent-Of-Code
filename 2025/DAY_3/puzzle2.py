import time

start = time.time()

with open("input.txt", "rt") as file:
    banks = file.read().splitlines()
sum = 0
bat_count = 12
for bank in banks:
    first_idx = len(bank) - bat_count
    bank_seq = list(bank[first_idx:])
    temp_seq = bank_seq.copy()
    for idx in range(first_idx - 1, -1, -1):
        if int(bank[idx]) >= int(bank_seq[0]):
            temp_seq[0] = bank[idx]
            for jdx in range(1, len(bank_seq), 1):
                if int(bank_seq[jdx - 1]) >= int(bank_seq[jdx]):
                    temp_seq[jdx] = bank_seq[jdx - 1]
                else:
                    break
        bank_seq = temp_seq.copy()
    sum += int("".join(bank_seq))

print(sum)
end = time.time()
print(f"{round(end - start, 4)}s")
