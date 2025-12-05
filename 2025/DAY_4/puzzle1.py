import time

start = time.time()

with open("input.txt", "rt") as file:
    wall_grid = file.read().splitlines()

sum = 0

checks_list = {
    "top": [(0, -1), (0, 1), (1, -1), (1, 0), (1, 1)],
    "bot": [(0, -1), (0, 1), (-1, -1), (-1, 0), (-1, 1)],
    "lef": [(-1, 0), (-1, 1), (0, 1), (1, 0), (1, 1)],
    "rig": [(-1, 0), (-1, -1), (0, -1), (1, 0), (1, -1)],
    "cen": [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)],
}


def is_roll_liftable(y_idx, x_idx):
    checks = checks_list["cen"]
    count = 0

    if y_idx == 0:
        # Return True if Top Corners
        if x_idx == 0 or x_idx == len(wall_grid[0]) - 1:
            return True
        checks = checks_list["top"]
    elif y_idx == len(wall_grid) - 1:
        # Return True if Bottom Corners
        if x_idx == 0 or x_idx == len(wall_grid[0]) - 1:
            return True
        checks = checks_list["bot"]
    elif x_idx == 0:
        # Left Side
        checks = checks_list["lef"]
    elif x_idx == len(wall_grid[0]) - 1:
        # Right Side
        checks = checks_list["rig"]

    for check in checks:
        if wall_grid[y_idx + check[0]][x_idx + check[1]] == "@":
            count += 1
    if count < 4:
        return True

    return False


for y_idx, row in enumerate(wall_grid):
    row = list(row)

    for x_idx, roll in enumerate(row):
        if roll == "@" and is_roll_liftable(y_idx=y_idx, x_idx=x_idx):
            sum += 1


print(sum)
end = time.time()
print(f"{round(end - start, 5)}s")
