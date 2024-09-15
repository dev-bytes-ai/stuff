#include <ncurses.h>
#include <unistd.h> // for usleep()

#define DELAY 30000 // Delay between frames (microseconds)
#define PADDLE_HEIGHT 4
#define PADDLE_WIDTH 1
#define BALL_SPEED 1

int max_y, max_x;
int ball_y, ball_x;
int ball_dir_y = BALL_SPEED, ball_dir_x = BALL_SPEED;
int paddle1_y, paddle2_y;

// Function to draw the paddles
void draw_paddle(int paddle_x, int paddle_y) {
  for (int i = 0; i < PADDLE_HEIGHT; ++i) {
    mvprintw(paddle_y + i, paddle_x, "|");
  }
}

// Function to draw the ball
void draw_ball() { mvprintw(ball_y, ball_x, "O"); }

// Function to move paddles
void move_paddle(int *paddle_y, int direction) {
  if (direction == -1 && *paddle_y > 0) { // Move up
    (*paddle_y)--;
  }
  if (direction == 1 && (*paddle_y + PADDLE_HEIGHT < max_y)) { // Move down
    (*paddle_y)++;
  }
}

// Function to handle ball movement
void move_ball() {
  ball_y += ball_dir_y;
  ball_x += ball_dir_x;

  // Ball collision with top and bottom walls
  if (ball_y <= 0 || ball_y >= max_y - 1) {
    ball_dir_y = -ball_dir_y;
  }

  // Ball collision with paddles
  if (ball_x == 2 && ball_y >= paddle1_y &&
      ball_y <= paddle1_y + PADDLE_HEIGHT - 1) {
    ball_dir_x = -ball_dir_x;
  }
  if (ball_x == max_x - 3 && ball_y >= paddle2_y &&
      ball_y <= paddle2_y + PADDLE_HEIGHT - 1) {
    ball_dir_x = -ball_dir_x;
  }

  // Ball out of bounds (left or right)
  if (ball_x <= 0 || ball_x >= max_x - 1) {
    ball_x = max_x / 2;
    ball_y = max_y / 2;
  }
}

int main() {
  // Initialize ncurses
  initscr();
  noecho();
  curs_set(FALSE);
  timeout(0);           // Non-blocking input
  keypad(stdscr, TRUE); // Enable arrow keys

  // Get screen size
  getmaxyx(stdscr, max_y, max_x);

  // Initialize ball position
  ball_y = max_y / 2;
  ball_x = max_x / 2;

  // Initialize paddle positions
  paddle1_y = max_y / 2 - PADDLE_HEIGHT / 2;
  paddle2_y = max_y / 2 - PADDLE_HEIGHT / 2;

  while (1) {
    clear();

    // Draw paddles and ball
    draw_paddle(1, paddle1_y);         // Left paddle
    draw_paddle(max_x - 2, paddle2_y); // Right paddle
    draw_ball();

    // Handle input for paddles
    int ch = getch();
    switch (ch) {
    case 'w':
      move_paddle(&paddle1_y, -1);
      break;
    case 's':
      move_paddle(&paddle1_y, 1);
      break;
    case KEY_UP:
      move_paddle(&paddle2_y, -1);
      break;
    case KEY_DOWN:
      move_paddle(&paddle2_y, 1);
      break;
    }

    // Move the ball
    move_ball();

    refresh();
    usleep(DELAY); // Pause for a moment
  }

  // End ncurses mode
  endwin();

  return 0;
}
