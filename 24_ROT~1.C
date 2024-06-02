#include <graphics.h>
#include <math.h>
#include <stdio.h>

// Function to draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

// Function to translate a point (x, y) by (tx, ty)
void translatePoint(int *x, int *y, int tx, int ty) {
    *x += tx;
    *y += ty;
}

// Function to rotate a point (x, y) about the origin by angle theta
void rotatePoint(int *x, int *y, float theta) {
    float rad = theta * (M_PI / 180.0); // Convert angle to radians
    int x_new = (*x * cos(rad) - *y * sin(rad));
    int y_new = (*x * sin(rad) + *y * cos(rad));
    *x = x_new;
    *y = y_new;
}

// Function to perform rotation about an arbitrary point (px, py)
void rotateAboutPoint(int *x, int *y, int px, int py, float theta) {
    // Translate point to the origin
    translatePoint(x, y, -px, -py);
    // Rotate point about the origin
    rotatePoint(x, y, theta);
    // Translate point back to its original position
    translatePoint(x, y, px, py);
}



int main() {
    int gd = DETECT, gm;
    
    // Original triangle vertices
    int x1 = 100, y1 = 100;
    int x2 = 150, y2 = 50;
    int x3 = 200, y3 = 100;
    
    // Rotate the triangle about the vertex (x1, y1)
    int x2_rot = x2, y2_rot = y2;
    int x3_rot = x3, y3_rot = y3;
    
    // Rotation angle
    float theta = 45.0;
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    // Draw original triangle
    drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
    delay(2000); // Delay to show the original triangle
    
rotateAboutPoint(&x2_rot, &y2_rot, x1, y1, theta);
rotateAboutPoint(&x3_rot, &y3_rot, x1, y1, theta);


    // Draw the rotated triangle
    drawTriangle(x1, y1, x2_rot, y2_rot, x3_rot, y3_rot, RED);
    delay(2000); // Delay to show the rotated triangle

    // Wait for a key press
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
