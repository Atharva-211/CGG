#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>

// Function to implement Bresenham's Line Algorithm
void bresenhamLine(int x1, int y1, int x2, int y2)
{
    int dx, dy, p, x, y;
    int xIncrement, yIncrement;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    xIncrement = (x2 > x1) ? 1 : -1;
    yIncrement = (y2 > y1) ? 1 : -1;
    x = x1;
    y = y1;

    putpixel(x, y, WHITE);
    if (dx > dy)
    {
        p = 2 * dy - dx;
        while (x != x2)
        {
            x += xIncrement;
            if (p < 0)
            {
                p += 2 * dy;
            }
            else
            {
                y += yIncrement;
                p += 2 * (dy - dx);
            }
            putpixel(x, y, WHITE);
        }
    }
    else
    {
        p = 2 * dx - dy;
        while (y != y2)
        {
            y += yIncrement;
            if (p < 0)
            {
                p += 2 * dx;
            }
            else
            {
                x += xIncrement;
                p += 2 * (dx - dy);
            }
            putpixel(x, y, WHITE);
        }
    }
}

// Function to draw a convex polygon
void drawPolygon(int polyX[], int polyY[], int n)
{
    int i;
    for (i = 0; i < n - 1; i++)
    {
        bresenhamLine(polyX[i], polyY[i], polyX[i + 1], polyY[i + 1]);
    }
    bresenhamLine(polyX[n - 1], polyY[n - 1], polyX[0], polyY[0]);
}

// Boundary Fill Algorithm
void boundaryFill(int x, int y, int boundaryColor, int fillColor)
{
    int currentColor;
    currentColor = getpixel(x, y);
    if (currentColor != boundaryColor && currentColor != fillColor)
    {
        putpixel(x, y, fillColor);
        boundaryFill(x + 1, y, boundaryColor, fillColor);
        boundaryFill(x - 1, y, boundaryColor, fillColor);
        boundaryFill(x, y + 1, boundaryColor, fillColor);
        boundaryFill(x, y - 1, boundaryColor, fillColor);
    }
}

int main()
{
    int gd = DETECT, gm;
    int polyX[] = {100, 130, 130, 100, 100};  // X-coordinates of polygon vertices
    int polyY[] = {200, 200, 250, 250, 200};  // Y-coordinates of polygon vertices

    int n = 5;  // Number of vertices
    int x = 101, y = 201;  // Starting point for boundary fill

    initgraph(&gd, &gm, "C:\\TurboC3\\BGI");

    // Draw the polygon
    drawPolygon(polyX, polyY, n);

    // Perform boundary fill
    boundaryFill(x, y, WHITE, GREEN);

    getch();
    closegraph();
    return 0;
}
