#include <graphics.h>
#include <conio.h>
#include <math.h>

// Function to draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

// Function to scale a triangle
void scaleTriangle(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, float sx, float sy) {
    *x1 *= sx;
    *y1 *= sy;
    *x2 *= sx;
    *y2 *= sy;
    *x3 *= sx;
    *y3 *= sy;
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
    int x1 = 100, y1 = 200, x2 = 200, y2 = 100, x3 = 300, y3 = 200;
    float sx, sy;
    int tx, ty;
    int choice;

    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    // Draw the original triangle
    setcolor(WHITE);
    drawTriangle(x1, y1, x2, y2, x3, y3);
    outtextxy(50, 50, "Original Triangle");

    printf("Choose an operation:\n");
    printf("1. Scale\n");
    printf("2. Translate\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter scaling factors (sx sy): ");
            scanf("%f %f", &sx, &sy);
            scaleTriangle(&x1, &y1, &x2, &y2, &x3, &y3, sx, sy);
            setcolor(GREEN);
            drawTriangle(x1, y1, x2, y2, x3, y3);
            outtextxy(50, 70, "Scaled Triangle");
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
