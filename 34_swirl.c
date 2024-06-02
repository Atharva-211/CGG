#include <graphics.h>
#include <cmath>
#include <conio.h>
#include <vector>

// Bresenham's circle drawing algorithm
void drawCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    while (y >= x) {
        putpixel(xc + x, yc + y, WHITE);
        putpixel(xc - x, yc + y, WHITE);
        putpixel(xc + x, yc - y, WHITE);
        putpixel(xc - x, yc - y, WHITE);
        putpixel(xc + y, yc + x, WHITE);
        putpixel(xc - y, yc + x, WHITE);
        putpixel(xc + y, yc - x, WHITE);
        putpixel(xc - y, yc - x, WHITE);
        x++;
        if (d > 0) {
            y--;
            d = d + 4 * (x - y) + 10;
        } else {
            d = d + 4 * x + 6;
        }
    }
}

int main() {
    // Initialize graphics mode
    int gd = DETECT, gm;
        // Constants for swirl motion
    const int centerX = getmaxx() / 2;
    const int centerY = getmaxy() / 2;
    const float radiusIncrement = 0.5;
    const float angleIncrement = 0.1;

    float angle = 0;
    float radius = 0;

    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    // Vector to store the path points
    std::vector<std::pair<int, int>> pathPoints;

    while (!kbhit()) {
        // Clear screen
        cleardevice();

        // Calculate ball's position
        int x = centerX + static_cast<int>(radius * cos(angle));
        int y = centerY + static_cast<int>(radius * sin(angle));

        // Draw the ball using Bresenham's circle drawing algorithm
        drawCircle(x, y, 10);

        // Add the current point to the path
        pathPoints.push_back(std::make_pair(x, y));

        // Draw the path
        if (pathPoints.size() > 1) {
            setcolor(YELLOW);
            for (size_t i = 1; i < pathPoints.size(); ++i) {
                line(pathPoints[i - 1].first, pathPoints[i - 1].second, pathPoints[i].first, pathPoints[i].second);
            }
        }

        // Update angle and radius for the swirl effect
        angle += angleIncrement;
        radius += radiusIncrement;

        // Add a short delay
        delay(30);
    }

    // Close the graphics mode
    closegraph();
    return 0;
}
