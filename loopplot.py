import matplotlib.pyplot as plt
import re
# paste output into data string block
data = """
(1,2)(1,1)(2,1)(3,1)(3,2)(3,3)(2,3)(1,3)(1,2)
"""

def all_symmetries(loop, grid_size):
    order_rotations = [tuple(loop[i:] + loop[:i]) for i in range(len(loop))]
    
    rotations = [
        lambda p: p,
        lambda p: [(y, grid_size + 1 - x) for x, y in p],
        lambda p: [(grid_size + 1 - x, grid_size + 1 - y) for x, y in p],
        lambda p: [(grid_size + 1 - y, x) for x, y in p]
    ]
    
    mirror = lambda p: [(y, x) for x, y in p]
    
    return {
        tuple(transformation)
        for order in order_rotations
        for rot in rotations
        for transformation in (
            rot(order),
            mirror(rot(order)),
            list(reversed(rot(order))),
            list(reversed(mirror(rot(order))))
        )
    }

def filter_loops(loops):
    grid_size = max(max(x, y) for loop in loops for (x, y) in loop)
    seen = set()
    unique_loops = []
    for loop in loops:
        loop = loop[:-1]
        sym_set = all_symmetries(loop, grid_size)
        if sym_set & seen:
            continue
        loop.append(loop[0])
        unique_loops.append(loop)
        seen.update(sym_set)
        
    return unique_loops

lines = data.strip().split('\n')
loops = []
for line in lines:
        loop = [(int(x), int(y)) for x, y in re.findall(r"\((\d+),(\d+)\)", line)]
        loops.append(loop)

loops = filter_loops(loops)

print("\n", len(loops))
for loop in loops:
    for t in loop:
        print(f"({t[0]},{t[1]})", end="")
    print()

figs = []
for i, loop in enumerate(loops):
    x_coords, y_coords = zip(*loop)

    fig, ax = plt.subplots(figsize=(6, 6))
    ax.plot(x_coords, y_coords, marker='o', linestyle='-', color='b', markersize=5)

    for x, y in loop:
        ax.text(x, y, f"({x},{y})", fontsize=9)

    ax.grid(True)
    ax.set_title(f"Loop {i+1}")
    ax.set_xticks(range(min(x_coords)-1, max(x_coords)+2))
    ax.set_yticks(range(min(y_coords)-1, max(y_coords)+2))

    figs.append(fig)

plt.show()