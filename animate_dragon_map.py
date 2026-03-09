import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.animation import FuncAnimation, PillowWriter

ROWS = 10
COLS = 10

# Special cells
special_cells = {
    (0, 3): "D",
    (1, 4): "T",
    (2, 8): "C",
    (4, 5): "D",
    (7, 7): "D",
}

cell_colors = {
    "D": "#fca5a5",   # light red
    "T": "#93c5fd",   # light blue
    "C": "#fcd34d",   # light yellow
}

# Zigzag path
path = []
for r in range(ROWS):
    if r % 2 == 0:
        for c in range(COLS):
            path.append((r, c))
    else:
        for c in reversed(range(COLS)):
            path.append((r, c))

# Precompute simple simulation stats
hp_values = []
time_values = []
event_values = []

hp = 100
total_time = 0

for pos in path:
    event = "Traversal"
    total_time += 1  # base traversal cost

    if pos in special_cells:
        kind = special_cells[pos]
        if kind == "D":
            hp -= 10
            total_time += 5
            event = "Battle: Dragon"
        elif kind == "T":
            total_time += 8
            event = "Special: Time Illusion Dragon"
        elif kind == "C":
            total_time += 6
            event = "Special: Chaos Reversing Dragon"

    hp_values.append(max(hp, 0))
    time_values.append(total_time)
    event_values.append(event)


def draw_grid(ax):
    ax.set_xlim(0, COLS)
    ax.set_ylim(0, ROWS)
    ax.set_aspect("equal")
    ax.invert_yaxis()
    ax.set_xticks(range(COLS + 1))
    ax.set_yticks(range(ROWS + 1))
    ax.grid(True, linewidth=1)
    ax.set_xticklabels([])
    ax.set_yticklabels([])
    ax.tick_params(length=0)


def draw_cells(ax, current_pos):
    for r in range(ROWS):
        for c in range(COLS):
            face = "white"
            edge = "#666666"
            lw = 1.0

            if (r, c) in special_cells:
                face = cell_colors[special_cells[(r, c)]]

            if (r, c) == current_pos and (r, c) in special_cells:
                edge = "black"
                lw = 2.5

            rect = patches.Rectangle(
                (c, r), 1, 1,
                edgecolor=edge,
                facecolor=face,
                linewidth=lw
            )
            ax.add_patch(rect)

    for (r, c), label in special_cells.items():
        ax.text(c + 0.5, r + 0.55, label, ha="center", va="center",
                fontsize=12, fontweight="bold", color="black")


def draw_path(ax, step):
    if step > 0:
        xs = [p[1] + 0.5 for p in path[:step + 1]]
        ys = [p[0] + 0.5 for p in path[:step + 1]]
        ax.plot(xs, ys, linewidth=2)


def draw_warrior(ax, pos):
    r, c = pos
    circle = patches.Circle((c + 0.5, r + 0.5), 0.25)
    ax.add_patch(circle)
    ax.text(c + 0.5, r + 0.5, "W", ha="center", va="center",
            fontsize=11, fontweight="bold", color="white")


def draw_sidebar(fig, step):
    pos = path[step]
    row, col = pos
    hp = hp_values[step]
    total_time = time_values[step]
    event = event_values[step]

    info = (
        f"Position: ({row}, {col})\n"
        f"HP: {hp}\n"
        f"Total Time: {total_time}\n"
        f"Mode: Zigzag Traversal\n"
        f"Event: {event}\n"
        f"Progress: {step + 1}/{len(path)}"
    )

    legend = (
        "Legend\n"
        "W = Warrior\n"
        "D = Dragon\n"
        "T = Time Illusion Dragon\n"
        "C = Chaos Reversing Dragon\n"
        "Blue line = Traversed Path"
    )

    fig.text(
        0.77, 0.72, info,
        fontsize=11, va="top",
        bbox=dict(boxstyle="round", facecolor="white", alpha=0.9)
    )

    fig.text(
        0.77, 0.38, legend,
        fontsize=10, va="top",
        bbox=dict(boxstyle="round", facecolor="white", alpha=0.9)
    )


fig = plt.figure(figsize=(11, 8))
ax = fig.add_axes([0.08, 0.12, 0.6, 0.78])  # leave room for sidebar


def update(frame):
    fig.clear()
    ax = fig.add_axes([0.08, 0.12, 0.6, 0.78])

    current_pos = path[frame]

    draw_grid(ax)
    draw_cells(ax, current_pos)
    draw_path(ax, frame)
    draw_warrior(ax, current_pos)

    ax.set_title(
        f"Dragon Training Simulation\nStep {frame + 1}/{len(path)}",
        fontsize=14
    )

    draw_sidebar(fig, frame)


anim = FuncAnimation(
    fig,
    update,
    frames=len(path),
    interval=200,
    repeat=False
)

anim.save("dragon_simulation.gif", writer=PillowWriter(fps=5))
print("dragon_simulation.gif generated")