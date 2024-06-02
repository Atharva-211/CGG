#include <graphics.h>
#include <math.h>
#include <stdio.h>

// Function to implement DDA Line Drawing Algorithm
void ddaLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    float x = x1;
    float y = y1;
    int i;
    for (i = 0; i <= steps; i++) {
	putpixel(x, y, WHITE);
	x += x_inc;
	y += y_inc;
    }
}

// Function to implement Bresenham's Circle Drawing Algorithm
void bresenhamCircle(int xc, int yc, int r) {
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

void drawClockFace(int xc, int yc, int r) {
    int i;
    bresenhamCircle(xc, yc, r);
    for ( i = 0; i < 12; i++) {
	float angle = i * M_PI / 6;
	int x1 = xc + (r - 10) * cos(angle);
	int y1 = yc + (r - 10) * sin(angle);
	int x2 = xc + r * cos(angle);
	int y2 = yc + r * sin(angle);
	ddaLine(x1, y1, x2, y2);
    }
}

void drawHand(int xc, int yc, int r, float angle) {
    int x = xc + r * cos(angle);
    int y = yc + r * sin(angle);
    ddaLine(xc, yc, x, y);
}

int main() {
    int gd = DETECT, gm;
	int xc = 300, yc = 300, r = 200;
    float angle = -M_PI / 2; // Start at the 12 o'clock position
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");



    while (!kbhit()) {
        cleardevice();
        // Draw the clock face
        drawClockFace(xc, yc, r);

        // Draw the clock hand
        drawHand(xc, yc, r - 20, angle);

        delay(100); // Delay for smooth animation

        angle += M_PI / 180; // Rotate the hand

        if (angle >= 2 * M_PI) {
            angle -= 2 * M_PI;
        }
    }

    closegraph();
    return 0;
}
