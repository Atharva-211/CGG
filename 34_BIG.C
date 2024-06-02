#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>

#define PI 3.14159265

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
    
    // Big Circle properties
    int bigCenterX = 320, bigCenterY = 240; // Center coordinates of the big circle
    int bigRadius = 100;                     // Radius of the big circle

    // Small Circle properties
    int smallRadius = 20;                    // Radius of the small circle
    double angle = 0;                        // Initial angle for small circle's position
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");


    while (!kbhit()) { // Continue until a key is pressed
	// Clear screen

        // Calculate the position of the small circle
	int smallCenterX = bigCenterX + (bigRadius - smallRadius) * cos(angle * PI / 180);
        int smallCenterY = bigCenterY + (bigRadius - smallRadius) * sin(angle * PI / 180);

        cleardevice();

        // Draw big circle using Bresenham's algorithm
        drawCircle(bigCenterX, bigCenterY, bigRadius);

        // Draw small circle using Bresenham's algorithm
        drawCircle(smallCenterX, smallCenterY, smallRadius);

        // Increment angle for next frame
        angle += 1; // You can adjust the angular velocity here

        // Delay to control animation speed
        delay(50);
    }

    // Close graphics
    closegraph();
    return 0;
}
