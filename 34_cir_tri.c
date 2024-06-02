#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

#define PI 3.14159265

// Bresenham's line drawing algorithm
void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
    int err = dx + dy, e2;

    while (!kbhit()) {
        putpixel(x1, y1, WHITE); // Set the pixel at (x1, y1)
        if (x1 == x2 && y1 == y2) break;
        e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y1 += sy;
        }
    }
}

// Bresenham's circle drawing algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x) {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

int main() {
    int gd = DETECT, gm;
        // Triangle vertices
    int x1 = 200, y1 = 300;  // Top vertex
    int x2 = 300, y2 = 300;  // Right vertex
    int x3 = 200, y3 = 400;  // Bottom-left vertex

    // Calculate equations of the lines representing triangle sides
    float slope1 = (float)(y2 - y1) / (x2 - x1);
    float slope2 = (float)(y3 - y2) / (x3 - x2);
    float slope3 = (float)(y3 - y1) / (x3 - x1);

    // Determine the side lengths of the triangle
    float side1 = sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)); // Length of side opposite to angle 90 degrees
    float side2 = sqrt(pow((x3 - x2), 2) + pow((y3 - y2), 2)); // Length of side opposite to angle 45 degrees
    float side3 = sqrt(pow((x3 - x1), 2) + pow((y3 - y1), 2)); // Length of side opposite to angle 45 degrees

    // Find the hypotenuse (longest side)
    float hypotenuse = (side1 > side2 && side1 > side3) ? side1 : ((side2 > side1 && side2 > side3) ? side2 : side3);

    // Ball properties
    int ballRadius = 10;    // Radius of the ball
    int ballX = x1, ballY = y1; // Initial position of the ball (start from top vertex)
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");



    while (ballY <= y3) { // Continue until ball reaches the bottom of the triangle
        // Clear screen
        cleardevice();

        // Draw triangle using Bresenham's line algorithm
        drawLine(x1, y1, x2, y2);
        drawLine(x2, y2, x3, y3);
        drawLine(x3, y3, x1, y1);

        // Draw ball using Bresenham's circle algorithm
        drawCircle(ballX, ballY, ballRadius);

        // Calculate next position of the ball along the hypotenuse
        ballX += 1; // Move 1 unit horizontally
        ballY = (int)(y1 + slope1 * (ballX - x1)); // Calculate corresponding y-coordinate on the hypotenuse

        // Delay to control animation speed
        delay(50);
    }

    // Close graphics
    closegraph();
    return 0;
}
