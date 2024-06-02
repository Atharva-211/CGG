#include <graphics.h>
#include <math.h>

// Function to draw a triangle
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

// Function to rotate a point around another point (cx, cy)
void rotatePoint(int *x, int *y, int cx, int cy, float angle) {
    float theta = angle * (3.14159 / 180.0);
    int x_new = (int)(cx + (*x - cx) * cos(theta) - (*y - cy) * sin(theta));
    int y_new = (int)(cy + (*x - cx) * sin(theta) + (*y - cy) * cos(theta));
    *x = x_new;
    *y = y_new;
}

// Function to rotate a triangle
void rotateTriangle(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, float angle) {
    // Calculate the centroid of the triangle
    int cx = (*x1 + *x2 + *x3) / 3;
    int cy = (*y1 + *y2 + *y3) / 3;

    // Rotate each vertex around the centroid
    rotatePoint(x1, y1, cx, cy, angle);
    rotatePoint(x2, y2, cx, cy, angle);
    rotatePoint(x3, y3, cx, cy, angle);
}

// Function to translate a triangle
void translateTriangle(int *x1, int *y1, int *x2, int *y2, int *x3, int *y3, int dx, int dy) {
    *x1 += dx;
    *y1 += dy;
    *x2 += dx;
    *y2 += dy;
    *x3 += dx;
    *y3 += dy;
}

int main() {
    int gd = DETECT, gm;
       // Original triangle vertices
    int x1 = 200, y1 = 200;
    int x2 = 250, y2 = 300;
    int x3 = 150, y3 = 300;

    // Angles for rotation
    float theta1 = 30.0;
    float theta2 = 45.0; 

        // Rotate by theta1 then theta2
    int x1_rot1 = x1, y1_rot1 = y1;
    int x2_rot1 = x2, y2_rot1 = y2;
    int x3_rot1 = x3, y3_rot1 = y3;

        // Rotate by theta2 then theta1
    int x1_rot2 = x1, y1_rot2 = y1;
    int x2_rot2 = x2, y2_rot2 = y2;
    int x3_rot2 = x3, y3_rot2 = y3;
    
initgraph(&gd, &gm, "C:\\TurboC3\\BGI");



    // Draw original triangle
    drawTriangle(x1, y1, x2, y2, x3, y3, WHITE);
    delay(1000); // Delay to show the original triangle


rotateTriangle(&x1_rot1, &y1_rot1, &x2_rot1, &y2_rot1, &x3_rot1, &y3_rot1, theta1);
translateTriangle(&x1_rot1, &y1_rot1, &x2_rot1, &y2_rot1, &x3_rot1, &y3_rot1,  100, 0);
    drawTriangle(x1_rot1, y1_rot1, x2_rot1, y2_rot1, x3_rot1, y3_rot1, 8);

rotateTriangle(&x1_rot1, &y1_rot1, &x2_rot1, &y2_rot1, &x3_rot1, &y3_rot1, theta2);
translateTriangle(&x1_rot1, &y1_rot1, &x2_rot1, &y2_rot1, &x3_rot1, &y3_rot1, 0, 100);

    // Draw triangle after rotating by theta1 then theta2 (red)
    drawTriangle(x1_rot1, y1_rot1, x2_rot1, y2_rot1, x3_rot1, y3_rot1, RED);
    delay(1000); // Delay to show the rotation by theta1 then theta2


rotateTriangle(&x1_rot2, &y1_rot2, &x2_rot2, &y2_rot2, &x3_rot2, &y3_rot2, theta2);
translateTriangle(&x1_rot2, &y1_rot2, &x2_rot2, &y2_rot2, &x3_rot2, &y3_rot2,  150, 0);
   drawTriangle(x1_rot2, y1_rot2, x2_rot2, y2_rot2, x3_rot2, y3_rot2, GREEN);

rotateTriangle(&x1_rot2, &y1_rot2, &x2_rot2, &y2_rot2, &x3_rot2, &y3_rot2, theta1);
translateTriangle(&x1_rot2, &y1_rot2, &x2_rot2, &y2_rot2, &x3_rot2, &y3_rot2, 0,150);


    // Draw triangle after rotating by theta2 then theta1 (blue)
    drawTriangle(x1_rot2, y1_rot2, x2_rot2, y2_rot2, x3_rot2, y3_rot2, BLUE);
    delay(1000); // Delay to show the rotation by theta2 then theta1

    // Wait for a key press
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
