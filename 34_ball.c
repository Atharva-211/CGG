#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

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
    int gd = DETECT, gm, i;
    int r = 10, x1, y1, x2, y2, x3, y3;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    x1 = 286, y1 = 150;
    for (i = 0; i < 49; i++) {
        cleardevice();
        drawLine(200, 250, 300, 150);
        drawLine(300, 150, 400, 250);
        drawLine(200, 250, 400, 250);
        drawCircle(x1, y1, r);
        x1 -= 2;
        y1 += 2;
        delay(35);
    }

    x2 = 210, y2 = 260;
    for (i = 0; i < 97; i++) {
        cleardevice();
        drawLine(200, 250, 300, 150);
        drawLine(300, 150, 400, 250);
        drawLine(200, 250, 400, 250);
        drawCircle(x2, y2, r);
        x2 += 2;
        delay(35);
    }

    x3 = 415, y3 = 250;
    for (i = 0; i < 55; i++) {
        cleardevice();
        drawLine(200, 250, 300, 150);
        drawLine(300, 150, 400, 250);
        drawLine(200, 250, 400, 250);
        drawCircle(x3, y3, r);
        x3 -= 2;
        y3 -= 2;
        delay(35);
    }

    x3 = 314, y3 = 150;
    for (i = 0; i < 50; i++) {
        cleardevice();
        drawLine(200, 250, 300, 150);
        drawLine(300, 150, 400, 250);
        drawLine(200, 250, 400, 250);
        drawCircle(x3, y3, r);
        x3 += 2;
        y3 += 2;
        delay(35);
    }

    x2 = 410, y2 = 260;
    for (i = 0; i < 107; i++) {
        cleardevice();
        drawLine(200, 250, 300, 150);
        drawLine(300, 150, 400, 250);
        drawLine(200, 250, 400, 250);
        drawCircle(x2, y2, r);
        x2 -= 2;
        delay(35);
    }

    x1 = 186, y1 = 250;
    for (i = 0; i < 55; i++) {
        cleardevice();
        drawLine(200, 250, 300, 150);
        drawLine(300, 150, 400, 250);
        drawLine(200, 250, 400, 250);
        drawCircle(x1, y1, r);
        x1 += 2;
        y1 -= 2;
        delay(35);
    }

    getch();
    closegraph();
}
