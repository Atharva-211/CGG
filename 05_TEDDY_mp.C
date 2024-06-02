#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

void drawCircleMidpoint(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 1 - r;

    while (x <= y) {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);

        x++;
        if (p < 0) {
            p += 2 * x + 1;
        } else {
            y--;
            p += 2 * (x - y) + 1;
        }
    }
}

void drawTeddyBearFace(int xc, int yc) {
    // Draw face
    drawCircleMidpoint(xc, yc, 100);
    // Draw left ear
    drawCircleMidpoint(xc - 70, yc - 70, 30);
    // Draw right ear
    drawCircleMidpoint(xc + 70, yc - 70, 30);
    // Draw left eye
    drawCircleMidpoint(xc - 40, yc - 20, 10);
    // Draw right eye
    drawCircleMidpoint(xc + 40, yc - 20, 10);
    // Draw nose
    drawCircleMidpoint(xc, yc + 20, 10);
}

int main() {
    int gd = DETECT, gm;
    int xc = 250, yc = 250;  // Move declaration here
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    drawTeddyBearFace(xc, yc);

    getch();
    closegraph();
    return 0;
}
