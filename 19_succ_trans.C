#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>

// Function to draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

// Function to translate a triangle
void translateTriangle(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int tx, int ty) {
    *x1 += tx;
    *y1 += ty;
    *x2 += tx;
    *y2 += ty;
    *x3 += tx;
    *y3 += ty;
}

int main() {
    int gd = DETECT, gm;

    // Original triangle vertices
    int x1 = 100, y1 = 100;
    int x2 = 150, y2 = 200;
    int x3 = 50, y3 = 200;

    // Translation values
    int dx1 = 50, dy1 = 50;
    int dx2 = 100, dy2 = 100;

    // First translation (dx1, dy1)
    int x1_t1 = x1, y1_t1 = y1;
    int x2_t1 = x2, y2_t1 = y2;
    int x3_t1 = x3, y3_t1 = y3;

    // Second translation (dx2, dy2) after first translation
    int x1_t2 = x1, y1_t2 = y1;
    int x2_t2 = x2, y2_t2 = y2;
    int x3_t2 = x3, y3_t2 = y3;

    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    // Draw original triangle
    drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
    delay(1000); // Delay to show the original triangle

    // First translation
    translateTriangle(&x1_t1, &y1_t1, &x2_t1, &y2_t1, &x3_t1, &y3_t1, dx1, dy1);
    drawTriangle(x1_t1, y1_t1, x2_t1, y2_t1, x3_t1, y3_t1, RED);
    delay(1000); // Delay to show the first translation

    // Second translation after first translation
    translateTriangle(&x1_t1, &y1_t1, &x2_t1, &y2_t1, &x3_t1, &y3_t1, dx2, dy2);
    drawTriangle(x1_t1, y1_t1, x2_t1, y2_t1, x3_t1, y3_t1, BLUE);
    delay(1000); // Delay to show the second translation

    // First translation
    translateTriangle(&x1_t2, &y1_t2, &x2_t2, &y2_t2, &x3_t2, &y3_t2, dx2, dy2);
    drawTriangle(x1_t2, y1_t2, x2_t2, y2_t2, x3_t2, y3_t2, GREEN);
    delay(1000); // Delay to show the first translation

    // Second translation after first translation
    translateTriangle(&x1_t2, &y1_t2, &x2_t2, &y2_t2, &x3_t2, &y3_t2, dx1, dy1);
    drawTriangle(x1_t2, y1_t2, x2_t2, y2_t2, x3_t2, y3_t2, YELLOW);
    delay(1000); // Delay to show the second translation

    // Wait for a key press
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
