#include <graphics.h>
#include <stdio.h>

// Function to perform X shear transformation
void shearX(int x, int y, float shx) {
    x = x + shx * y;
}

// Function to perform Y shear transformation
void shearY(int x, int y, float shy) {
    y = y + shy * x;
}

// Function to shear points
void shear(int x[], int y[], int n, float shx, float shy) {
    int i;
    for (i = 0; i < n; i++) {
	x[i] += shx * y[i];
	y[i] += shy * x[i];
    }
}

// Function to draw a line using DDA algorithm
void dda(int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = (float)dx / (float)steps;
    float yIncrement = (float)dy / (float)steps;
    float x = x1, y = y1;
    int i;
    for (i = 0; i <= steps; i++) {
	putpixel(x, y, color);
	x += xIncrement;
	y += yIncrement;
    }
}

// Function to draw a polygon
void drawPolygon(int x[], int y[], int n, int color) {
    int i;
    for (i = 0; i < n - 1; i++) {
        dda(x[i], y[i], x[i + 1], y[i + 1], color);
    }
    dda(x[n - 1], y[n - 1], x[0], y[0], color);
}

int main() {
    int gd = DETECT, gm;
        // Original hexagon vertices
    int poly_x[] = {100,260,260,100,100};
    int poly_y[] = {50 ,50 ,150,150,50};
    int n = sizeof(poly_x) / sizeof(poly_x[0]);
        // Shear factors
    float shx, shy;
    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");
    
    drawPolygon(poly_x, poly_y, n, WHITE);
    printf("Enter shear factors (shx shy): ");
    scanf("%f %f", &shx, &shy);

    // Shear the hexagon vertices
    shear(poly_x, poly_y, n, shx, shy);

    // Draw the sheared hexagon
    drawPolygon(poly_x, poly_y, n, WHITE);

    // Wait for a key press
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
