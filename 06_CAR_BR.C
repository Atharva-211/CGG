#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

// Function to draw a line using Bresenham's algorithm
void drawLineBresenham(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    int e2;
    
    while (1) {
        putpixel(x0, y0, WHITE);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

// Function to draw a circle using Bresenham's algorithm
void drawCircleBresenham(int xc, int yc, int r) {
    int x = 0;
    int y = r;
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
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    // Draw the car body
    drawLineBresenham(100, 300, 400, 300); // bottom line
    drawLineBresenham(100, 300, 100, 250); // left vertical line
    drawLineBresenham(100, 250, 150, 200); // left diagonal line
    drawLineBresenham(150, 200, 350, 200); // top horizontal line
    drawLineBresenham(350, 200, 400, 250); // right diagonal line
    drawLineBresenham(400, 250, 400, 300); // right vertical line

    // Draw the windows
    drawLineBresenham(175, 200, 175, 250); // left window left vertical
    drawLineBresenham(175, 200, 250, 200); // left window top horizontal
    drawLineBresenham(250, 200, 250, 250); // left window right vertical
    drawLineBresenham(175, 250, 250, 250); // left window bottom horizontal

    drawLineBresenham(275, 200, 275, 250); // right window left vertical
    drawLineBresenham(275, 200, 350, 200); // right window top horizontal
    drawLineBresenham(350, 200, 350, 250); // right window right vertical
    drawLineBresenham(275, 250, 350, 250); // right window bottom horizontal

    // Draw the bonnet
    drawLineBresenham(100, 250, 50, 250); // bonnet top horizontal line
    drawLineBresenham(50, 250, 50, 300);  // bonnet left vertical line
    drawLineBresenham(50, 300, 100, 300); // bonnet bottom horizontal line

    // Draw the car wheels
    drawCircleBresenham(150, 325, 25); // left wheel
    drawCircleBresenham(350, 325, 25); // right wheel

    getch();
    closegraph();

    return 0;
}
