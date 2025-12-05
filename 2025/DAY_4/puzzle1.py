import time

start = time.time()

with open("test.txt", "rt") as file:
    wall_grid = file.read().splitlines()

sum = 0

checks_list = {
    "top": [(0, -1), (0, 1), (1, -1), (1, 0), (1, -1)],
    "bot": [(0, -1), (0, 1), (-1, -1), (-1, 0), (-1, -1)],
    "lef": [(-1, 0), (-1, 1), (0, 1), (1, 0), (1, 1)],
    "rig": [(-1, 0), (-1, -1), (0, -1), (1, 0), (1, -1)],
    "cen": [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)],
}


def is_roll_liftable(y_idx, x_idx):
    if y_idx == 0:
        # Return True if Top Corners
        if x_idx == 0 or x_idx == len(wall_grid[0]) - 1:
            return True
        else:
            count = 0
            for checks in checks_list["top"]:
                if wall_grid[y_idx + checks[0]][x_idx + checks[1]] == "@":
                    count += 1
                # print(checks[0], end=" ")
            if count < 4:
                return True
            # print(wall_grid[y_idx - 1][x_idx], end="")
    return False


for y_idx, row in enumerate(wall_grid):
    row = list(row)
    for x_idx, roll in enumerate(row):
        if roll == "@":
            bool = is_roll_liftable(y_idx=y_idx, x_idx=x_idx)
            if bool:
                sum += 1

        # print(wall_grid[y_idx][x_idx], end="")
    # print()

print(sum)
end = time.time()
print(f"{round(end - start, 5)}s")
