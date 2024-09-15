const canvas = document.getElementById('gameCanvas');
const ctx = canvas.getContext('2d');

canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

const squareSize = 50;
let squareX = canvas.width / 2 - squareSize / 2;
let squareY = canvas.height / 2 - squareSize / 2;
const speed = 5;

function drawSquare() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    ctx.fillStyle = 'blue';
    ctx.fillRect(squareX, squareY, squareSize, squareSize);
}

function update() {
    drawSquare();
}

function moveSquare(event) {
    switch(event.key) {
        case 'ArrowUp':
            if (squareY - speed >= 0) squareY -= speed;
            break;
        case 'ArrowDown':
            if (squareY + speed <= canvas.height - squareSize) squareY += speed;
            break;
        case 'ArrowLeft':
            if (squareX - speed >= 0) squareX -= speed;
            break;
        case 'ArrowRight':
            if (squareX + speed <= canvas.width - squareSize) squareX += speed;
            break;
    }
    update();
}

window.addEventListener('keydown', moveSquare);
update();

