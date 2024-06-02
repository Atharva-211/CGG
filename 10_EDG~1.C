#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

// Function to implement Bresenham's Line Algorithm
void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx, dy, p, x, y;
    int xIncrement, yIncrement;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    xIncrement = (x2 > x1) ? 1 : -1;
    yIncrement = (y2 > y1) ? 1 : -1;
    x = x1;
    y = y1;

    putpixel(x, y, WHITE);
    if (dx > dy) {
        p = 2 * dy - dx;
        while (x != x2) {
            x += xIncrement;
            if (p < 0) {
                p += 2 * dy;
            } else {
                y += yIncrement;
                p += 2 * (dy - dx);
            }
            putpixel(x, y, WHITE);
        }
    } else {
        p = 2 * dx - dy;
        while (y != y2) {
            y += yIncrement;
            if (p < 0) {
                p += 2 * dx;
            } else {
                x += xIncrement;
                p += 2 * (dx - dy);
            }
            putpixel(x, y, WHITE);
        }
    }
}

// Function to draw a convex polygon (triangle) and its edges
void drawConvexPolygon(int polyX[], int polyY[]) {
    // Draw edges of the triangle
    bresenhamLine(polyX[0], polyY[0], polyX[1], polyY[1]);
    bresenhamLine(polyX[1], polyY[1], polyX[2], polyY[2]);
    bresenhamLine(polyX[2], polyY[2], polyX[0], polyY[0]);
}

// Edge Fill Algorithm for convex polygons
void edgeFill(int polyX[], int polyY[], int fillColor) {
    int i, j;
    int  INT_MAX ,INT_MIN;
    int yMin = INT_MAX, yMax = INT_MIN;

    // Find the minimum and maximum y-coordinates of the triangle
    for (i = 0; i < 3; i++) {
        if (polyY[i] < yMin) yMin = polyY[i];
        if (polyY[i] > yMax) yMax = polyY[i];
    }

    // For each scanline, fill the pixels between the edges
    for (i = yMin + 1; i < yMax; i++) {
        int intersections[2];
        int count = 0;

        // Find intersections of the scanline with the edges
        for (j = 0; j < 3; j++) {
            int next = (j + 1) % 3;
            if ((polyY[j] < i && polyY[next] >= i) || (polyY[next] < i && polyY[j] >= i)) {
                intersections[count++] = polyX[j] + (i - polyY[j]) * (polyX[next] - polyX[j]) / (polyY[next] - polyY[j]);
            }
        }

        // Sort intersections in ascending order
        if (intersections[0] > intersections[1]) {
            int temp = intersections[0];
            intersections[0] = intersections[1];
            intersections[1] = temp;
        }

        // Fill the pixels between intersections
        for (j = intersections[0] + 1; j < intersections[1]; j++) {
            putpixel(j, i, fillColor);
        }
    }
}

int main() {
    int gd = DETECT, gm;
    int polyX[] = {200, 100, 300};  // X-coordinates of triangle vertices
    int polyY[] = {100, 300, 300};  // Y-coordinates of triangle vertices

    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    // Draw the convex polygon (triangle) and its edges
    drawConvexPolygon(polyX, polyY);

    // Perform edge fill
    edgeFill(polyX, polyY, GREEN);

    // Wait for a key press
    getch();

    // Close the graphics mode
    closegraph();

    return 0;
}
