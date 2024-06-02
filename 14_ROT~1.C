#include <graphics.h>
#include <stdio.h>
#include <math.h>

// Function to draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

// Function to rotate a point (x, y) by angle degrees
void rotatePoint(int *x, int *y, float angle) {
    float radians = angle * M_PI / 180.0;
    int newX = *x * cos(radians) - *y * sin(radians);
    int newY = *x * sin(radians) + *y * cos(radians);
    *x = newX;
    *y = newY;
}

// Function to rotate a triangle
void rotateTriangle(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, float angle) {
    rotatePoint(x1, y1, angle);
    rotatePoint(x2, y2, angle);
    rotatePoint(x3, y3, angle);
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
	// Original triangle coordinates
    int x1 = 100, y1 = 200;
    int x2 = 200, y2 = 100;
    int x3 = 300, y3 = 200;

	int choice;
    float angle;
    int tx, ty;
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");



    // Draw the original triangle
    setcolor(WHITE);
    drawTriangle(x1, y1, x2, y2, x3, y3);
    outtextxy(50, 50, "Original Triangle");



    printf("Choose an operation:\n");
    printf("1. Rotate\n");
    printf("2. Translate\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter rotation angle (in degrees): ");
            scanf("%f", &angle);
            rotateTriangle(&x1, &y1, &x2, &y2, &x3, &y3, angle);
            setcolor(GREEN);
            drawTriangle(x1, y1, x2, y2, x3, y3);
            outtextxy(50, 70, "Rotated Triangle");
            break;
        case 2:
            printf("Enter translation values (tx ty): ");
            scanf("%d %d", &tx, &ty);
            translateTriangle(&x1, &y1, &x2, &y2, &x3, &y3, tx, ty);
            setcolor(RED);
            drawTriangle(x1, y1, x2, y2, x3, y3);
            outtextxy(50, 90, "Translated Triangle");
            break;
        default:
            printf("Invalid choice!\n");
    }

    // Wait for a key press
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
