#include <graphics.h>
#include <conio.h>
#include <math.h>

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

void scaleTriangle(int x1, int y1, int x2, int y2, int x3, int y3, float sx, float sy) {
    x1 *= sx;
    y1 *= sy;
    x2 *= sx;
    y2 *= sy;
    x3 *= sx;
    y3 *= sy;

    drawTriangle(x1, y1, x2, y2, x3, y3);
}

void rotateTriangle(int x1, int y1, int x2, int y2, int x3, int y3, float angle) {
    float theta = angle * (3.14159 / 180.0);
    int x1_new = (x1 * cos(theta) - y1 * sin(theta));
    int y1_new = (x1 * sin(theta) + y1 * cos(theta));
    int x2_new = (x2 * cos(theta) - y2 * sin(theta));
    int y2_new = (x2 * sin(theta) + y2 * cos(theta));
    int x3_new = (x3 * cos(theta) - y3 * sin(theta));
    int y3_new = (x3 * sin(theta) + y3 * cos(theta));

    drawTriangle(x1_new, y1_new, x2_new, y2_new, x3_new, y3_new);
}


int main() {
    int gd = DETECT, gm;
    int x1 = 100, y1 = 200, x2 = 200, y2 = 100, x3 = 300, y3 = 200;
    float sx, sy, angle;
    int choice;

    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    // Draw the original triangle
    drawTriangle(x1, y1, x2, y2, x3, y3);

    // Take user input for scaling or rotation
    printf("Choose an operation:\n");
    printf("1. Scale\n");
    printf("2. Rotate\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter scaling factors (sx sy): ");
            scanf("%f %f", &sx, &sy);
            scaleTriangle(x1, y1, x2, y2, x3, y3, sx, sy);
            break;
        case 2:
            printf("Enter rotation angle (in degrees): ");
            scanf("%f", &angle);
            rotateTriangle(x1, y1, x2, y2, x3, y3, angle);
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
