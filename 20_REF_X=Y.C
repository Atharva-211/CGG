#include <graphics.h>
#include <stdio.h>
#include <math.h>

// Function to draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
    delay(1000); // Delay to show the triangle
}

// Function to reflect a point about the line y=x
void reflectAboutLineYX(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Function to reflect a point about the x-axis
void reflectAboutXAxis(int *x, int *y) {
    *y = -(*y);
}

// Function to rotate a point 90 degrees clockwise
void rotate90Clockwise(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = -temp;
}

int main() {
    int gd = DETECT, gm;

    // Original triangle vertices
    int x1 = 100, y1 = 100;
    int x2 = 200, y2 = 100;
    int x3 = 150, y3 = 200;

    // Reflection about the line y = x
    int x1_reflect1 = x1, y1_reflect1 = y1;
    int x2_reflect1 = x2, y2_reflect1 = y2;
    int x3_reflect1 = x3, y3_reflect1 = y3;

    // Reflection about the x-axis
    int x1_reflect2 = x1_reflect1, y1_reflect2 = y1_reflect1;
    int x2_reflect2 = x2_reflect1, y2_reflect2 = y2_reflect1;
    int x3_reflect2 = x3_reflect1, y3_reflect2 = y3_reflect1;

    // Rotation by 90 degrees counterclockwise
    int x1_transform = x1_reflect2, y1_transform = y1_reflect2;
    int x2_transform = x2_reflect2, y2_transform = y2_reflect2;
    int x3_transform = x3_reflect2, y3_transform = y3_reflect2;

    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    // Draw original triangle
    drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);

    reflectAboutLineYX(&x1_reflect1, &y1_reflect1);
    reflectAboutLineYX(&x2_reflect1, &y2_reflect1);
    reflectAboutLineYX(&x3_reflect1, &y3_reflect1);
    // Draw triangle after reflection about y = x (RED)
    drawTriangle(x1_reflect1, y1_reflect1, x2_reflect1, y2_reflect1, x3_reflect1, y3_reflect1, RED);

    reflectAboutXAxis(&x1_reflect2, &y1_reflect2);
    reflectAboutXAxis(&x2_reflect2, &y2_reflect2);
    reflectAboutXAxis(&x3_reflect2, &y3_reflect2);
    // Draw triangle after reflection about x-axis (GREEN)
    drawTriangle(x1_reflect2, y1_reflect2, x2_reflect2, y2_reflect2, x3_reflect2, y3_reflect2, GREEN);

    rotate90Clockwise(&x1_transform, &y1_transform);
    rotate90Clockwise(&x2_transform, &y2_transform);
    rotate90Clockwise(&x3_transform, &y3_transform);
    // Draw triangle after rotation (BLUE)
    drawTriangle(x1_transform, y1_transform, x2_transform, y2_transform, x3_transform, y3_transform, BLUE);

    // Wait for a key press
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
