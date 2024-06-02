#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
//T(dx1,dy1).T(dx2,dy2)=T(dx1+dx2,dy1+dy2)
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
    int x1 = 50, y1 = 50;
    int x2 = 100, y2 = 150;
    int x3 = 0, y3 = 150;

    // Combined translation directly from the original triangle
    int x1_combined = x1, y1_combined = y1;
    int x2_combined = x2, y2_combined = y2;
    int x3_combined = x3, y3_combined = y3;

    // Translation values
    int dx1 = 50, dy1 = 50;
    int dx2 = 100, dy2 = 120;

    // First translation
    int x1_t1 = x1, y1_t1 = y1;
    int x2_t1 = x2, y2_t1 = y2;
    int x3_t1 = x3, y3_t1 = y3;

    int x1_t2, x2_t2, x3_t2, y1_t2, y2_t2, y3_t2;
        initgraph(&gd, &gm, "C:\\TurboC3\\BGI");  // Initialize the graphics mode

    // Apply first translation
    translateTriangle(&x1_t1, &y1_t1, &x2_t1, &y2_t1, &x3_t1, &y3_t1, dx1, dy1);

    // Second translation based on first translation
    x1_t2 = x1_t1;
    y1_t2 = y1_t1;
    x2_t2 = x2_t1;
    y2_t2 = y2_t1;
    x3_t2 = x3_t1;
    y3_t2 = y3_t1;

    // Apply second translation
    translateTriangle(&x1_t2, &y1_t2, &x2_t2, &y2_t2, &x3_t2, &y3_t2, dx2, dy2);

    // Apply combined translation
    translateTriangle(&x1_combined, &y1_combined, &x2_combined, &y2_combined, &x3_combined, &y3_combined, dx1 + dx2, dy1 + dy2);

    // Draw original triangle
    drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
    outtextxy(x1, y1 - 10, "Original Triangle");
    delay(1000);
    // Draw triangle after first translation (red)
    drawTriangle(x1_t1, y1_t1, x2_t1, y2_t1, x3_t1, y3_t1, RED);
    outtextxy(x1_t1, y1_t1 - 10, "After First Translation");
     delay(1000);

    // Draw triangle after second translation (blue)
    drawTriangle(x1_t2, y1_t2, x2_t2, y2_t2, x3_t2, y3_t2, BLUE);
    outtextxy(x1_t2, y1_t2 - 10, "After Second Translation");
     delay(3000);

    // Draw the combined translated triangle (green)
    drawTriangle(x1_combined, y1_combined, x2_combined, y2_combined, x3_combined, y3_combined, GREEN);
    outtextxy(x1_combined, y1_combined - 10, "After Combined Translation");

    // Wait for a key press
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
