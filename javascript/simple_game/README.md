# Simple JavaScript Game

## Overview

This is a basic game built with HTML, CSS, and JavaScript. It features a movable square that you can control using the arrow keys. The game is designed to be a starting point for learning how to develop simple games with JavaScript.

## How to Run

1. **Clone the Repository** (or download the files):

    ```bash
    git clone <repository-url>
    ```

2. **Navigate to the Project Directory**:

    ```bash
    cd <project-directory>
    ```

3. **Open `index.html` in Your Browser**:

    You can either open the file directly or use a local server if you prefer. For example, you can use VS Code's Live Server extension.

## Files

- `index.html`: The HTML file that sets up the canvas and links to the JavaScript file.
- `game.js`: The JavaScript file that contains the game logic, including drawing the square and handling keyboard input.
- `style.css`: (Optional) CSS for styling the canvas and body (included in HTML).

## Features

- A blue square displayed on a canvas.
- Movement controls using the arrow keys.
- Basic boundary checks to ensure the square stays within the canvas.

## Key Functions

- `drawSquare()`: Clears the canvas and redraws the square at its current position.
- `update()`: Updates the game state by calling `drawSquare()`.
- `moveSquare(event)`: Moves the square based on the arrow key pressed and updates the canvas.

## Future Improvements

- Add obstacles or targets to interact with.
- Implement scoring and game-over conditions.
- Enhance visuals with images or animations.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- This project was created for educational purposes and is a simple introduction to game development with JavaScript.

## Contact

For questions or suggestions, please contact [Your Name] at [your.email@example.com].


