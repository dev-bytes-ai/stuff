import random

import pygame

# Initialize Pygame
pygame.init()

# Game settings
WIDTH, HEIGHT = 600, 600
CELL_SIZE = 40
COLS, ROWS = WIDTH // CELL_SIZE, HEIGHT // CELL_SIZE

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
GOLD = (255, 215, 0)  # Treasures
BLUE = (0, 0, 255)  # Traps

# Set up display
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Escape the Maze")

# Maze grid
maze = [[1 for _ in range(COLS)] for _ in range(ROWS)]  # 1 for wall, 0 for path
stack = []  # For DFS backtracking

# Directions: (dx, dy)
DIRECTIONS = [(0, -1), (0, 1), (-1, 0), (1, 0)]  # Up, Down, Left, Right


# Function to generate the maze using DFS
def generate_maze(x, y):
    maze[y][x] = 0  # Mark the current cell as a path
    stack.append((x, y))

    while stack:
        x, y = stack[-1]
        neighbors = []

        # Check for unvisited neighbors
        for dx, dy in DIRECTIONS:
            nx, ny = x + dx * 2, y + dy * 2  # Check 2 cells away
            if 0 <= nx < COLS and 0 <= ny < ROWS and maze[ny][nx] == 1:
                neighbors.append((nx, ny))

        if neighbors:
            # Choose a random neighbor
            nx, ny = random.choice(neighbors)

            # Remove the wall between current and chosen neighbor
            maze[y + (ny - y) // 2][x + (nx - x) // 2] = 0

            # Mark the neighbor as a path and add to stack
            maze[ny][nx] = 0
            stack.append((nx, ny))
        else:
            # Backtrack if no neighbors
            stack.pop()


# Generate the maze starting from the top-left corner
generate_maze(0, 0)

# Player settings
player_pos = [CELL_SIZE, CELL_SIZE]  # Start at top-left corner
player_speed = CELL_SIZE // 2
normal_speed = player_speed
slow_speed = CELL_SIZE // 4  # Speed reduced by traps
trap_effect_duration = 3000  # 3 seconds of slow effect

# Treasures and traps
treasures = []
traps = []


# Place treasures and traps in random path cells
def place_items(item_list, count, color):
    while len(item_list) < count:
        x, y = random.randint(0, COLS - 1), random.randint(0, ROWS - 1)
        if maze[y][x] == 0 and (x != 1 or y != 1):  # Ensure not on player start
            item_list.append((x * CELL_SIZE, y * CELL_SIZE))


place_items(treasures, 5, GOLD)  # Place 5 treasures
place_items(traps, 3, BLUE)  # Place 3 traps

# Clock and timer
clock = pygame.time.Clock()
timer = 30  # 30 seconds countdown

# Trap effect timer
trap_timer = 0

# Game loop
running = True
while running:
    screen.fill(WHITE)

    # Event handling
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Timer logic
    timer -= clock.tick(30) / 1000  # Decrease time each frame

    if timer <= 0:
        print("Time's up! You lose!")
        running = False

    # Player movement
    keys = pygame.key.get_pressed()
    if (
        keys[pygame.K_LEFT]
        and player_pos[0] > 0
        and maze[player_pos[1] // CELL_SIZE][player_pos[0] // CELL_SIZE - 1] == 0
    ):
        player_pos[0] -= player_speed
    if (
        keys[pygame.K_RIGHT]
        and player_pos[0] < WIDTH - CELL_SIZE
        and maze[player_pos[1] // CELL_SIZE][player_pos[0] // CELL_SIZE + 1] == 0
    ):
        player_pos[0] += player_speed
    if (
        keys[pygame.K_UP]
        and player_pos[1] > 0
        and maze[player_pos[1] // CELL_SIZE - 1][player_pos[0] // CELL_SIZE] == 0
    ):
        player_pos[1] -= player_speed
    if (
        keys[pygame.K_DOWN]
        and player_pos[1] < HEIGHT - CELL_SIZE
        and maze[player_pos[1] // CELL_SIZE + 1][player_pos[0] // CELL_SIZE] == 0
    ):
        player_pos[1] += player_speed

    # Check for treasure collection
    for treasure in treasures[:]:
        if player_pos[0] == treasure[0] and player_pos[1] == treasure[1]:
            treasures.remove(treasure)
            timer += 5  # Add 5 seconds to timer

    # Check for traps
    for trap in traps[:]:
        if player_pos[0] == trap[0] and player_pos[1] == trap[1]:
            traps.remove(trap)
            player_speed = slow_speed
            trap_timer = pygame.time.get_ticks()  # Set trap effect timer

    # Reset speed after trap effect duration
    if trap_timer and pygame.time.get_ticks() - trap_timer > trap_effect_duration:
        player_speed = normal_speed
        trap_timer = 0

    # Draw maze
    for row in range(ROWS):
        for col in range(COLS):
            if maze[row][col] == 1:  # Wall
                pygame.draw.rect(
                    screen,
                    BLACK,
                    (col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE),
                )

    # Draw treasures
    for treasure in treasures:
        pygame.draw.rect(screen, GOLD, (*treasure, CELL_SIZE, CELL_SIZE))

    # Draw traps
    for trap in traps:
        pygame.draw.rect(screen, BLUE, (*trap, CELL_SIZE, CELL_SIZE))

    # Draw player
    pygame.draw.rect(screen, RED, (*player_pos, CELL_SIZE, CELL_SIZE))

    # Draw exit (bottom-right corner)
    pygame.draw.rect(
        screen,
        GREEN,
        ((COLS - 2) * CELL_SIZE, (ROWS - 2) * CELL_SIZE, CELL_SIZE, CELL_SIZE),
    )

    # Check if player reaches the exit
    if (
        player_pos[0] == (COLS - 2) * CELL_SIZE
        and player_pos[1] == (ROWS - 2) * CELL_SIZE
    ):
        print("You win!")
        running = False

    # Update display
    pygame.display.flip()

# Quit game
pygame.quit()
